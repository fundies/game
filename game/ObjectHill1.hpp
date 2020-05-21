#ifndef ObjectHill1_HPP
#define ObjectHill1_HPP

#include "ObjectPlatform.hpp"

class ObjectHill1 : public ObjectPlatform {
 public:
  virtual ~ObjectHill1() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectHill1();
};

#endif
