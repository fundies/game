#ifndef COLLISIONINFO_HPP
#define COLLISIONINFO_HPP

#include "Types.hpp"

#include <Crash2D/collision.hpp>

class CollisionInfo : public Crash2D::Collision {
 public:
  CollisionInfo(Instance i, Crash2D::Collision c) : Crash2D::Collision(c), instance(i) {}
  Instance instance;
};

#endif
