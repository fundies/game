#ifndef ObjectPlatform_HPP
#define ObjectPlatform_HPP

#include "Object.hpp"

class ObjectPlatform : public Object {
 public:
  virtual ~ObjectPlatform() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

  float slope = 0.f;

 protected:
  ObjectPlatform();
  
};

#endif
