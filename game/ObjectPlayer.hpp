#ifndef ObjectPlayer_HPP
#define ObjectPlayer_HPP

#include "Object.hpp"
#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

class ObjectPlayer : public Object {
 public:
  virtual ~ObjectPlayer() {}
  static Instance Create(Transformation<float> t);
  void PostCollision(float dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer) override;
  void DrawGUI(BatchRenderer* renderer) override;

 protected:
  ObjectPlayer();

  float platformSlope = 0;
  Mask platformMask;
  unsigned platformBuffer = 0;
  float GetHspeedFactor(float spd);

 private:
  //float vSpeed;
  const float ladderClimbSpeed;
  const float jumpAccel;
  const float maxJumpSpeed;
  const float maxFallSpeed;
  const float fallAcceleration;
  const float trampolineMultiplier;
  float platformVspeed;

  //float hSpeed;
  const float defaultFriction;
  float horAccel;
  const float horAccelOnPlatform;
  const float horAccelInAir;
  float maxHspeed;
  float platformHspeed;

  bool isFalling;
  bool isJumping;
  bool canJump;
  bool onLadder;
  bool hitPlatform;
};

#endif
