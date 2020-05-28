#include "ObjectHill1.hpp"

#include "ResourceManager.hpp"

Instance ObjectHill1::Create(Transformation<float> t) {
  Instance inst(new ObjectHill1());
  inst->SetSprite(ResourceManager::GetSprite("hill_1"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("hill_1");

  mask.SetTranslation(t.GetTranslation() + Vec2f(0, 50));
  mask.SetPivot(Vec2f(t.GetPivot().x, 0));
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.Transform();

  inst->AddMask(mask);

  return inst;
}

ObjectHill1::ObjectHill1() { slope = 0.5f; }

void ObjectHill1::PostCollision(float dt) {}

void ObjectHill1::Collision(CollisionInfo collision) {}

void ObjectHill1::Draw(BatchRenderer* renderer) { Object::Draw(renderer); }

void ObjectHill1::DrawGUI(BatchRenderer* renderer) {}
