#ifndef ObjectHUD_HPP
#define ObjectHUD_HPP

#include "ConvexShape.hpp"
#include "Object.hpp"
#include "Text.hpp"

#include "Banner.hpp"
#include "KeyIcon.hpp"
#include "PlayerInfo.hpp"
#include "Wheel.hpp"

class ObjectHUD : public Object {
 public:
  virtual ~ObjectHUD() {}
  static Instance Create(Transformation<float_type> t);
  void Collision(CollisionInfo collision) override;
  void PostCollision(float_type dt) override;
  void Draw(BatchRenderer* _renderer, View& view) override;
  void DrawGUI(BatchRenderer* _renderer, View& view) override;

 protected:
  ObjectHUD();

  uint_t _currentPlayer;
  uint_t _playerTurn;
  uint_t _numPlayers;
  bool_t _donePlayerMoves;
  bool_t _viewingMap;
  vector_t<PlayerInfo> _players;
  ubyte_t _startAlpha;
  ubyte_t _endAlpha;
  ENGINE::Vector2<int_t> _hudSize;
  uint_t _hudSpacing;
  map_t<string_t, KeyIcon> _keys;
  Wheel _wheel;
  float_type _viewMapSpeed;
  Sprite _arrowSprite;
  Banner _banner[4];
};

#endif
