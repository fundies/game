#include "ObjectBlock.hpp"

#include "ResourceManager.hpp"

Instance ObjectBlock::Create(Transformation<float> t) {
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

  inst->AddMask(mask);

  return inst;
}

ObjectBlock::ObjectBlock() {}

void ObjectBlock::PostCollision(float dt) {}

void ObjectBlock::Collision(CollisionInfo collision) {}

void ObjectBlock::Draw(BatchRenderer* renderer) { Object::Draw(renderer); }

void ObjectBlock::DrawGUI(BatchRenderer* renderer) {}
