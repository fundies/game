#ifndef GAME_HPP
#define GAME_HPP

#include "BatchRenderer.hpp"
#include "Vector2.hpp"

enum GameState { GAME_ACTIVE, GAME_MENU, GAME_PAUSE };

class Game {
 public:
  Game(unsigned width, unsigned height);
  ~Game();
  void Init();
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
  //void SetHeight(const unsigned& _height);
  static void SetKey(unsigned key, bool pressed);
  void SetRenderer(BatchRenderer* _renderer);
  void SetState(const GameState& _state);
  //void SetWidth(const unsigned& _width);
  //const unsigned& GetHeight() const;
  BatchRenderer* GetRenderer();
  const GameState& GetState() const;
  //const unsigned& GetWidth() const;

  static void SetWindowSize(const Vec2i _windowSize);
  static const Vec2i GetWindowSize();

 protected:
  GameState _state;
  BatchRenderer* _renderer;
  static Vec2i _windowSize;
};

#endif
