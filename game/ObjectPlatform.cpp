#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

Instance ObjectPlatform::Create(Transformation<float> t) {
  Instance inst(new ObjectPlatform());
  return inst;
}

ObjectPlatform::ObjectPlatform() {}

void ObjectPlatform::PostCollision(float dt) {}

void ObjectPlatform::Collision(CollisionInfo collision) {}

void ObjectPlatform::Draw(BatchRenderer* renderer) {}

void ObjectPlatform::DrawGUI(BatchRenderer* renderer) {}
