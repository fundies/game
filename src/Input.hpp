#ifndef INPUT_HPP
#define INPUT_HPP

#include "ControlScheme.hpp"

#include <SDL.h>

#include <map>

class Gamepad {
 public:
  Gamepad();
  bool isConnected;
  float deadzone;

  bool ButtonPressed(GamepadButton id);
  bool ButtonHeld(GamepadButton id);
  bool ButtonReleased(GamepadButton id);

  void SetGamepadDown(int btn);
  void SetGamepadUp(int btn);
  void SetAxisValue(int axis, float value);
  void UpdateAxes();

 protected:
  bool Left();
  bool Right();
  bool Up();
  bool Down();

  bool _buttonPressed[SDL_CONTROLLER_BUTTON_MAX];
  bool _buttonHeld[SDL_CONTROLLER_BUTTON_MAX];
  bool _buttonReleased[SDL_CONTROLLER_BUTTON_MAX];

  bool _axisPressed[SDL_CONTROLLER_AXIS_MAX];
  bool _axisHeld[SDL_CONTROLLER_AXIS_MAX];
  bool _axisReleased[SDL_CONTROLLER_AXIS_MAX];

  float _axes[SDL_CONTROLLER_AXIS_MAX];
};

class Input {
 public:
  static Input& Get();
  
  static void KeyDown(int key);
  static void KeyUp(int key);
  static void GamepadDown(int id, int btn);
  static void GamepadUp(int id, int btn);

  static void SetControlScheme(ControlScheme& controls);

  static bool ButtonPressed(GameControl id);
  static bool ButtonHeld(GameControl id);
  static bool ButtonReleased(GameControl id);

  static void ResetButtons();
  
  static void BindController(int id);
  static void SetAxisValue(int ctrlrID, int axis, float value);

 protected:
  Input(void) {}
  Input(Input const&);           // prevent copies
  void operator=(Input const&);  // prevent assignments
  static ControlScheme _controls;

  static std::map<int, bool> _keyPressed;
  static std::map<int, bool> _keyHeld;
  static std::map<int, bool> _keyReleased;

  static Gamepad _gamepad[4];
  static SDL_GameController* _controllers[4];
};

#endif
