#ifndef GAME_HPP
#define GAME_HPP

#include "BatchRenderer.hpp"
#include "Vector2.hpp"

enum GameState { GAME_ACTIVE, GAME_MENU, GAME_PAUSE };

class Game {
 public:
  Game(uint_t width, uint_t height);
  ~Game();
  void Init();
  void ProcessInput(float_type dt);
  void Update(float_type dt);
  void Render();
  //void SetHeight(const uint_t& _height);
  static void SetKey(uint_t key, bool pressed);
  void SetRenderer(BatchRenderer* _renderer);
  void SetState(const GameState& _state);
  //void SetWidth(const uint_t& _width);
  //const uint_t& GetHeight() const;
  BatchRenderer* GetRenderer();
  const GameState& GetState() const;
  //const uint_t& GetWidth() const;

  static void SetWindowSize(const ENGINE::Vector2<int_t> _windowSize);
  static const ENGINE::Vector2<int_t> GetWindowSize();

 protected:
  GameState _state;
  BatchRenderer* _renderer;
  static ENGINE::Vector2<int_t> _windowSize;
};

#endif
