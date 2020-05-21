#ifndef ObjectHill2_HPP
#define ObjectHill2_HPP

#include "ObjectPlatform.hpp"

class ObjectHill2 : public ObjectPlatform {
 public:
  virtual ~ObjectHill2() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectHill2();
};

#endif
