#include "ObjectCollectible.hpp"

#include "ResourceManager.hpp"

Instance ObjectCollectible::Create(Transformation<float_type> t) {
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

void ObjectCollectible::PostCollision(float_type dt) {}

void ObjectCollectible::Collision(CollisionInfo collision) {}

void ObjectCollectible::Draw(BatchRenderer* renderer, View& view) { Object::Draw(renderer, view); }

void ObjectCollectible::DrawGUI(BatchRenderer* renderer, View& view) {}
