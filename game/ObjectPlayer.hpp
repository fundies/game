#ifndef ObjectPlayer_HPP
#define ObjectPlayer_HPP

#include "Object.hpp"
#include "ObjectPlatform.hpp"
#include "ResourceManager.hpp"

class ObjectPlayer : public Object {
 public:
  virtual ~ObjectPlayer() {}
  static Instance Create(Transformation<float_type> t);
  void PostCollision(float_type dt) override;
  void Collision(CollisionInfo collision) override;
  void Draw(BatchRenderer* renderer, View& view) override;
  void DrawGUI(BatchRenderer* renderer, View& view) override;

 protected:
  ObjectPlayer();

  float platformSlope = 0;
  Mask platformMask;
  unsigned platformBuffer = 0;
  float GetHspeedFactor(float spd);

 private:
  //float_type vSpeed;
  const float_type ladderClimbSpeed;
  const float_type jumpAccel;
  const float_type maxJumpSpeed;
  const float_type maxFallSpeed;
  const float_type fallAcceleration;
  const float_type trampolineMultiplier;
  float_type platformVspeed;

  //float_type hSpeed;
  const float_type defaultFriction;
  float_type horAccel;
  const float_type horAccelOnPlatform;
  const float_type horAccelInAir;
  float_type maxHspeed;
  float_type platformHspeed;

  bool isFalling;
  bool isJumping;
  bool canJump;
  bool onLadder;
  bool hitPlatform;
};

#endif
