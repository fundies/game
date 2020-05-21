#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

Instance ObjectPlatform::Create(Transformation<float_type> t) {
  Instance inst(new ObjectPlatform());
  return inst;
}

ObjectPlatform::ObjectPlatform() {}

void ObjectPlatform::PostCollision(float_type dt) {}

void ObjectPlatform::Collision(CollisionInfo collision) {}

void ObjectPlatform::Draw(BatchRenderer* renderer, View& view) {}

void ObjectPlatform::DrawGUI(BatchRenderer* renderer, View& view) {}
