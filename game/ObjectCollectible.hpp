#ifndef ObjectCollectible_HPP
#define ObjectCollectible_HPP

#include "Object.hpp"

class ObjectCollectible : public Object {
 public:
  virtual ~ObjectCollectible() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectCollectible();
};

#endif
