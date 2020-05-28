#include "ObjectHill2.hpp"

#include "ResourceManager.hpp"

Instance ObjectHill2::Create(Transformation<float> t) {
  Instance inst(new ObjectHill2());
  inst->SetSprite(ResourceManager::GetSprite("hill_2"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("hill_2");
  mask.SetTranslation(t.GetTranslation());
  mask.SetPivot(inst->GetSprite().GetCenter());
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.Transform();

  inst->AddMask(mask);

  return inst;
}

ObjectHill2::ObjectHill2() {}

void ObjectHill2::PostCollision(float dt) {}

void ObjectHill2::Collision(CollisionInfo collision) {}

void ObjectHill2::Draw(BatchRenderer* renderer) { Object::Draw(renderer); }

void ObjectHill2::DrawGUI(BatchRenderer* renderer) {}
