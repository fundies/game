#ifndef ObjectHill1_HPP
#define ObjectHill1_HPP

#include "ObjectPlatform.hpp"

class ObjectHill1 : public ObjectPlatform {
 public:
  virtual ~ObjectHill1() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectHill1();
};

#endif
