#include "Game.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Logger.hpp"

#include <glad/glad.h>

#include <SDL.h>
#include <SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <functional>

#ifdef __ANDROID__
  #define GL_MAJOR 2
  #define GL_MINOR 0
  #define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
#else
  #define GL_MAJOR 3
  #define GL_MINOR 0
  #define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
#endif

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                     const GLchar* message, const void* userParam);

// The Width of the screen
const GLuint SCREEN_WIDTH = 1280;
// The height of the screen
const GLuint SCREEN_HEIGHT = 720;

Game Gaym(SCREEN_WIDTH, SCREEN_HEIGHT);

std::function<void()> loop;
void main_loop() { loop(); }

int main(int argc, char* argv[]) {
  bool exitGame = false;

  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER)) {
    PrintMessage("Failed to intialize sdl: %s", SDL_GetError());
    return -1;
  }
  
  if(!( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG )) { 
    PrintMessage( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
  #ifndef _WIN32
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  #endif


  SDL_Window* window = SDL_CreateWindow("GAYM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);
  
  if (window == nullptr) {
    PrintMessage("Failed to create window: %s", SDL_GetError());
    return -1;
  }
  
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);

  if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
    PrintMessage("Failed to initialize glad");
    exitGame = true;
  }

  // Check OpenGL properties
  PrintMessage("OpenGL loaded");
  PrintMessage("Vendor: %s", glGetString(GL_VENDOR));
  PrintMessage("Renderer: %s", glGetString(GL_RENDERER));
  PrintMessage("Version:  %s", glGetString(GL_VERSION));

  // OpenGL configuration
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /*if (glDebugMessageCallback) {
    PrintMessage("Register OpenGL debug callback ");
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openglCallbackFunction, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
  } else
    PrintMessage("glDebugMessageCallback not available");*/

  // Initialize game
  Gaym.Init();

  // Start Game within Menu State
  Gaym.SetState(GAME_ACTIVE);

  static double limitFPS = 1.0 / 60.0;

  double lastTime = (SDL_GetTicks() / (double)1000), timer = lastTime;
  double deltaTime = 0, nowTime = 0;
  int frames = 0, updates = 0;

  /*while (!exitGame)*/
  loop = [&] {
    // - Measure time
    nowTime = (SDL_GetTicks() / (double)1000);
    deltaTime += (nowTime - lastTime) / limitFPS;
    lastTime = nowTime;

    // - Only update at 60 frames / s
    while (deltaTime >= 1.0) {
      Gaym.ProcessInput(1);
      Gaym.Update(1);
      updates++;
      deltaTime--;
      Input::ResetButtons();
    }

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT: {
          exitGame = true;
          break;
        }
        case SDL_KEYDOWN: {
          Input::KeyDown(e.key.keysym.sym);
          break;
        }
        case SDL_KEYUP: {
          Input::KeyUp(e.key.keysym.sym);
          break;
        }
        case SDL_WINDOWEVENT: {
          switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
              Game::SetWindowSize(ENGINE::Vector2<int_t>(e.window.data1, e.window.data2));
              break;
            }
            break;
          }
        }
        case SDL_CONTROLLERDEVICEADDED: {
          int id = e.cdevice.which;
          if (SDL_IsGameController(id)) {
            if (id < 4) {
              PrintMessage("%s added as controller %i", SDL_GameControllerNameForIndex(e.cdevice.which), id);
              Input::BindController(id);
            } else {
              PrintMessage("Unable to add %s maximum controller count (4) reached", SDL_GameControllerNameForIndex(e.cdevice.which), id);
            }
          }
          break;
        }
        case SDL_CONTROLLERAXISMOTION: {
          int id = e.cdevice.which;
          Input::SetAxisValue(id, e.jaxis.axis, e.jaxis.value/32767.f);
          break;
        }
        case SDL_CONTROLLERBUTTONDOWN: {
          Input::GamepadDown(e.cdevice.which, e.cbutton.button); 
          break;
        }
        case SDL_CONTROLLERBUTTONUP: {
          Input::GamepadUp(e.cdevice.which, e.cbutton.button); 
          break;
        }
      }
    }

    // Render

    Gaym.Render();
    SDL_GL_SwapWindow(window);

    frames++;

    // - Reset after one second
    if ((SDL_GetTicks() / (double)1000) - timer > 1.0) {
      timer++;
      PrintMessage("FPS: %i Updates: %i", frames, updates);
      updates = 0, frames = 0;
    }
  };
  
	#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(main_loop, 0, true);
	#else
		while(!exitGame) main_loop();
	#endif

  // Delete all resources as loaded using the resource manager
  ResourceManager::Clear();

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

using std::cout;
using std::endl;
/*void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                     const GLchar* message, const void* userParam) {
  cout << "---------------------opengl-callback-start------------" << endl;
  cout << "message: " << message << endl;
  cout << "type: ";

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      cout << "ERROR";
      break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      cout << "DEPRECATED_BEHAVIOR";
      break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      cout << "UNDEFINED_BEHAVIOR";
      break;

    case GL_DEBUG_TYPE_PORTABILITY:
      cout << "PORTABILITY";
      break;

    case GL_DEBUG_TYPE_PERFORMANCE:
      cout << "PERFORMANCE";
      break;

    case GL_DEBUG_TYPE_OTHER:
      cout << "OTHER";
      break;
  }

  cout << endl;

  cout << "id: " << id << endl;
  cout << "severity: ";

  switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
      cout << "LOW";
      break;

    case GL_DEBUG_SEVERITY_MEDIUM:
      cout << "MEDIUM";
      break;

    case GL_DEBUG_SEVERITY_HIGH:
      cout << "HIGH";
      break;
  }

  cout << endl;
  cout << "---------------------opengl-callback-end--------------" << endl;
}*/
