#include "ObjectBlock.hpp"

#include "ResourceManager.hpp"

Instance ObjectBlock::Create(Transformation<float_type> t) {
  Instance inst(new ObjectBlock());
  inst->SetSprite(ResourceManager::GetSprite("block"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("block");
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.SetTranslation(t.GetTranslation());

  mask.Transform();

  inst->SetMask(mask);

  return inst;
}

ObjectBlock::ObjectBlock() {}

void ObjectBlock::PostCollision(float_type dt) {}

void ObjectBlock::Collision(CollisionInfo collision) {}

void ObjectBlock::Draw(BatchRenderer* renderer, View& view) { Object::Draw(renderer, view); }

void ObjectBlock::DrawGUI(BatchRenderer* renderer, View& view) {}
