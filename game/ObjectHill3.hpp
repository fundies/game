#ifndef ObjectHill3_HPP
#define ObjectHill3_HPP

#include "ObjectPlatform.hpp"

class ObjectHill3 : public ObjectPlatform {
 public:
  virtual ~ObjectHill3() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectHill3();

};

#endif
