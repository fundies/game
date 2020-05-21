#include "ObjectHill3.hpp"

#include "ResourceManager.hpp"

Instance ObjectHill3::Create(Transformation<float_type> t) {
  Instance inst(new ObjectHill3());
  inst->SetSprite(ResourceManager::GetSprite("hill_3"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("hill_3");
  mask.SetTranslation(t.GetTranslation());
  mask.SetPivot(inst->GetSprite().GetCenter());
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.Transform();

  inst->SetMask(mask);

  return inst;
}

ObjectHill3::ObjectHill3() : ObjectPlatform() { slope = 1.0f; }

void ObjectHill3::PostCollision(float_type dt) {}

void ObjectHill3::Collision(CollisionInfo collision) {}

void ObjectHill3::Draw(BatchRenderer* renderer, View& view) { Object::Draw(renderer, view); }

void ObjectHill3::DrawGUI(BatchRenderer* renderer, View& view) {}
