#include "ObjectHill2.hpp"

#include "ResourceManager.hpp"

Instance ObjectHill2::Create(Transformation<float_type> t) {
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

  inst->SetMask(mask);

  return inst;
}

ObjectHill2::ObjectHill2() {}

void ObjectHill2::PostCollision(float_type dt) {}

void ObjectHill2::Collision(CollisionInfo collision) {}

void ObjectHill2::Draw(BatchRenderer* renderer, View& view) { Object::Draw(renderer, view); }

void ObjectHill2::DrawGUI(BatchRenderer* renderer, View& view) {}
