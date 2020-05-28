#ifndef ObjectBlock_HPP
#define ObjectBlock_HPP

#include "ObjectPlatform.hpp"

class ObjectBlock : public ObjectPlatform {
 public:
  virtual ~ObjectBlock() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectBlock();
};

#endif
