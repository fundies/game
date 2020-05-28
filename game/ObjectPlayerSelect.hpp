#ifndef ObjectPlayerSelect_HPP
#define ObjectPlayerSelect_HPP

#include "Object.hpp"
#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

class ObjectPlayerSelect : public Object {
 public:
  virtual ~ObjectPlayerSelect() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void DrawGUI(BatchRenderer* _renderer) override;

 protected:
  ObjectPlayerSelect();

  unsigned currSelectColumn;
  unsigned selectColumns;
  unsigned currSelectRow;
  unsigned selectRows;
  bool changedSelection;

  unsigned currentPlayer;
  unsigned playerCount;

  ConvexShape banner;
  Vec2f bannerStartPos;
  Vec2f bannerPos;
  Vec2f bannerEndPos;
  Vec2f bannerOffset;
  float bannerSpeed;

  Vec2f charIconOffset;

  Sprite _nameIconSpr;
  Vec2f _nameIconOffset;
};

#endif
