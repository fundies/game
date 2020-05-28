#include "ObjectHill3.hpp"

#include "ResourceManager.hpp"

Instance ObjectHill3::Create(Transformation<float> t) {
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

  inst->AddMask(mask);

  return inst;
}

ObjectHill3::ObjectHill3() : ObjectPlatform() { slope = 1.0f; }

void ObjectHill3::PostCollision(float dt) {}

void ObjectHill3::Collision(CollisionInfo collision) {}

void ObjectHill3::Draw(BatchRenderer* renderer) { Object::Draw(renderer); }

void ObjectHill3::DrawGUI(BatchRenderer* renderer) {}
