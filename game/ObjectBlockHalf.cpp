#include "ObjectBlockHalf.hpp"

#include "ResourceManager.hpp"

Instance ObjectBlockHalf::Create(Transformation<float_type> t) {
  Instance inst(new ObjectBlockHalf());
  inst->SetSprite(ResourceManager::GetSprite("block half"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("block_half");
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.SetTranslation(t.GetTranslation());

  mask.Transform();

  inst->SetMask(mask);

  return inst;
}

ObjectBlockHalf::ObjectBlockHalf() {}

void ObjectBlockHalf::PostCollision(float_type dt) {}

void ObjectBlockHalf::Collision(CollisionInfo collision) {}

void ObjectBlockHalf::Draw(BatchRenderer* renderer, View& view) { Object::Draw(renderer, view); }

void ObjectBlockHalf::DrawGUI(BatchRenderer* renderer, View& view) {}
