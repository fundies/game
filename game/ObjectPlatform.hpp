#ifndef ObjectPlatform_HPP
#define ObjectPlatform_HPP

#include "Object.hpp"

class ObjectPlatform : public Object {
 public:
  virtual ~ObjectPlatform() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

  float slope = 0.f;

 protected:
  ObjectPlatform();
  
};

#endif
