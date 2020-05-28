#include "ObjectCollectible.hpp"

#include "ResourceManager.hpp"

Instance ObjectCollectible::Create(Transformation<float> t) {
  Instance inst(new ObjectCollectible());
  inst->SetSprite(ResourceManager::GetSprite("collectible"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());

  /*Mask mask = ResourceManager::GetMask("hill_1");
	mask.SetScale(t.GetScale());
	mask.SetRotation(t.GetRotation());
	mask.SetTranslation(t.GetTranslation())

	inst->SetMask(mask);*/

  return inst;
}

ObjectCollectible::ObjectCollectible() {}

void ObjectCollectible::PostCollision(float dt) {}

void ObjectCollectible::Collision(CollisionInfo collision) {}

void ObjectCollectible::Draw(BatchRenderer* renderer) { Object::Draw(renderer); }

void ObjectCollectible::DrawGUI(BatchRenderer* renderer) {}
