#ifndef ObjectBlockHalf_HPP
#define ObjectBlockHalf_HPP

#include "ObjectPlatform.hpp"

class ObjectBlockHalf : public ObjectPlatform {
 public:
  virtual ~ObjectBlockHalf() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectBlockHalf();
};

#endif
