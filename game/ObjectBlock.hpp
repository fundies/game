#ifndef ObjectBlock_HPP
#define ObjectBlock_HPP

#include "ObjectPlatform.hpp"

class ObjectBlock : public ObjectPlatform {
 public:
  virtual ~ObjectBlock() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectBlock();
};

#endif
