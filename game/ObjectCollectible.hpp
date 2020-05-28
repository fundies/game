#ifndef ObjectCollectible_HPP
#define ObjectCollectible_HPP

#include "Object.hpp"

class ObjectCollectible : public Object {
 public:
  virtual ~ObjectCollectible() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectCollectible();
};

#endif
