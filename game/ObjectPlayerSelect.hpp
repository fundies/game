#ifndef ObjectPlayerSelect_HPP
#define ObjectPlayerSelect_HPP

#include "Object.hpp"
#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

class ObjectPlayerSelect : public Object {
 public:
  virtual ~ObjectPlayerSelect() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void DrawGUI(BatchRenderer* _renderer, View& view) override;

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
  ENGINE::Vector2<float> bannerStartPos;
  ENGINE::Vector2<float> bannerPos;
  ENGINE::Vector2<float> bannerEndPos;
  ENGINE::Vector2<float> bannerOffset;
  float bannerSpeed;

  ENGINE::Vector2<float> charIconOffset;

  Sprite _nameIconSpr;
  ENGINE::Vector2<float> _nameIconOffset;
};

#endif
