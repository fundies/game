#ifndef ObjectHill2_HPP
#define ObjectHill2_HPP

#include "ObjectPlatform.hpp"

class ObjectHill2 : public ObjectPlatform {
 public:
  virtual ~ObjectHill2() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectHill2();
};

#endif
