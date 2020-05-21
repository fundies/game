#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "BatchRenderer.hpp"
#include "CollisionInfo.hpp"
#include "Input.hpp"
#include "Mask.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"

#include <iostream>
#include <memory>

static std::map<unsigned, unsigned> InstanceMax;

class Object : public Transformable {
 public:
  static Instance Create(Transformation<float_type> t);
  virtual void PostCollision(float_type dt) = 0;
  virtual void Collision(CollisionInfo collision){};
  virtual void Draw(BatchRenderer* _renderer, View& view);
  virtual void DrawGUI(BatchRenderer* _renderer, View& view) = 0;
  void SetMask(const Mask& _mask);
  void SetSprite(const Sprite& _sprite);
  Mask& GetMask();
  const Sprite& GetSprite() const;
  void SetStatic(const bool_t& _isStatic);
  const bool_t& IsStatic() const;
  Crash2D::Collision GetCollision(Instance other);
  void AddCollision(CollisionInfo collision);
  void ClearCollisions();

  float_type hSpeed = 0;
  float_type vSpeed = 0;

  Mask _mask;

  int_t ID = -1;

 protected:
  Object(int type = -1) : _isStatic(true) { if (type >= 0) ID = InstanceMax[type]++; }
  Sprite _sprite;
  std::vector<CollisionInfo> _collisions;
  bool_t _isStatic;
};

#endif
