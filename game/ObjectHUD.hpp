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
  static Instance Create(Transformation<float> t);
  void Collision(CollisionInfo collision) override;
  void PostCollision(float dt) override;
  void Draw(BatchRenderer* _renderer) override;
  void DrawGUI(BatchRenderer* _renderer) override;

 protected:
  ObjectHUD();

  unsigned _currentPlayer;
  unsigned _playerTurn;
  unsigned _numPlayers;
  bool _donePlayerMoves;
  bool _viewingMap;
  std::vector<PlayerInfo> _players;
  GLubyte _startAlpha;
  GLubyte _endAlpha;
  Vec2i _hudSize;
  unsigned _hudSpacing;
  std::map<std::string, KeyIcon> _keys;
  Wheel _wheel;
  float _viewMapSpeed;
  Sprite _arrowSprite;
  Banner _banner[4];
};

#endif
