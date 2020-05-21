#ifndef ObjectBlockHalf_HPP
#define ObjectBlockHalf_HPP

#include "ObjectPlatform.hpp"

class ObjectBlockHalf : public ObjectPlatform {
 public:
  virtual ~ObjectBlockHalf() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectBlockHalf();
};

#endif
