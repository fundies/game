#include "ObjectPlayer.hpp"

using Vec2 = Vec2f;

Instance ObjectPlayer::Create(Transformation<float> t) {
  Instance inst(new ObjectPlayer());
  inst->SetSprite(ResourceManager::GetSprite("mask_greg"));

  inst->SetScale(t.GetScale());
  inst->SetRotation(t.GetRotation());
  inst->SetTranslation(t.GetTranslation());
  inst->SetPivot(t.GetPivot());

  Mask mask = ResourceManager::GetMask("mask_greg");
  mask.SetScale(t.GetScale());
  mask.SetRotation(t.GetRotation());
  mask.SetTranslation(t.GetTranslation());

  mask.Transform();

  inst->AddMask(mask);

  return inst;
}

ObjectPlayer::ObjectPlayer()
    : Object(1),
      ladderClimbSpeed(3.0f),
      jumpAccel(8.75f),
      maxJumpSpeed(35.f),
      maxFallSpeed(40.f),
      fallAcceleration(2.f),
      trampolineMultiplier(-1.2f),
      platformVspeed(0.0f),

      defaultFriction(1.f),
      horAccel(1.f),
      horAccelOnPlatform(1.f),
      horAccelInAir(0.5f),
      maxHspeed(15.0f),

      isFalling(true),
      isJumping(false),
      canJump(false),
      onLadder(false),
      hitPlatform(false) {
  SetStatic(false);
}

float ObjectPlayer::GetHspeedFactor(float spd) {
  return spd - ((platformSlope/2) * spd * platformMask.GetScale().x * sgn(hSpeed));
}

void ObjectPlayer::PostCollision(float dt) {
  SetTranslation(_mask[0].GetTranslation() - Vec2(0, GetSprite().GetHeight() - _mask[0].Height()));

  int hdir = 0;
  if (ID == 0)
    hdir = Input::ButtonHeld(GameControl::Right) - Input::ButtonHeld(GameControl::Left);
 
  // Horizontal Movement
  float currHorrizontalAccel = (isJumping || isFalling) ? horAccelInAir : GetHspeedFactor(horAccel);
  float currMaxHspeed = GetHspeedFactor(maxHspeed);

  if (hdir != 0 && std::abs(hSpeed) < currMaxHspeed)
    hSpeed += hdir * currHorrizontalAccel;
  else if (std::abs(hSpeed) > 0) {
    if (hdir == 0 && std::abs(hSpeed) < GetHspeedFactor(defaultFriction))
      hSpeed = 0;
    else
      hSpeed -= sgn(hSpeed) * GetHspeedFactor(defaultFriction);
  }
  
  //hSpeed = hdir * 8;

  // Vertical Movement
  if (_collisions.size() == 0) isFalling = true;
  
  if (ID == 0 && Input::ButtonPressed(GameControl::A) && canJump) isJumping = true;

  if (!Input::ButtonHeld(GameControl::A)) isJumping = false;

  if (!isFalling && !isJumping && platformSlope != 0) {
    if ((_mask[0].Bottom - 100) < platformMask.Top) vSpeed = -platformSlope * hSpeed * platformMask.GetScale().x;
  }

  if (isJumping) {
    canJump = false;

    vSpeed -= jumpAccel;
    vSpeed = std::max(vSpeed, -maxJumpSpeed);

    if (vSpeed == -maxJumpSpeed) {
      isJumping = false;
      isFalling = true;
    }
  }

  else if (isFalling) {
    platformSlope = 0;
    canJump = false;
    vSpeed += fallAcceleration;
    vSpeed = std::min(vSpeed, maxFallSpeed);
  } else vSpeed = 0;
}

void ObjectPlayer::Collision(CollisionInfo collision) {
  if (auto p = dynamic_cast<ObjectPlatform*>(collision.instance.get())) {
    platformSlope = p->slope;
    platformMask = p->GetMask(0);
  }

  Vec2f t(collision.GetDisplacement().x, collision.GetDisplacement().y);

  if (platformSlope != 0) {
    if (std::abs(t.x) < 0.25) t.x = 0;

    if (std::abs(t.y) < 0.25) t.y = 0;
  }

  _mask[0].Translate(-t);
  _mask[0].Transform();

  if (t.y != 0) {
    if (t.y > 0) {
      isFalling = false;
      canJump = true;
      vSpeed -= t.y;
    } else {
      vSpeed = fallAcceleration;
      isJumping = false;
      isFalling = true;
    }
  } else {
    if (t.x != 0) hSpeed += -t.x;
  }
}

void ObjectPlayer::Draw(BatchRenderer* renderer) { 
  Object::Draw(renderer);
  renderer->DrawLine(GetTranslation(), GetTranslation() + Vec2(100, 0), Color::Red());
  //renderer->DrawCircle(Vec2(GetTranslation().x + GetWidth()/2, GetTranslation().y + GetHeight() - 30), 30);
}

void ObjectPlayer::DrawGUI(BatchRenderer* renderer) {
  //Object::DrawGUI(renderer);
}
