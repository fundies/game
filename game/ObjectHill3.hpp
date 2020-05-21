#ifndef ObjectHill3_HPP
#define ObjectHill3_HPP

#include "ObjectPlatform.hpp"

class ObjectHill3 : public ObjectPlatform {
 public:
  virtual ~ObjectHill3() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectHill3();

};

#endif
