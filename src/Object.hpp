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
  static Instance Create(Transformation<float> t);
  virtual void PostCollision(float dt) = 0;
  virtual void Collision(CollisionInfo collision){};
  virtual void Draw(BatchRenderer* _renderer);
  virtual void DrawGUI(BatchRenderer* _renderer) = 0;
  void SetMask(int id, const Mask& _mask);
  void SetSprite(const Sprite& _sprite);
  void AddMask(const Mask& mask) { _mask.push_back(mask); }
  Mask& GetMask(int id);
  std::vector<Mask>& GetMasks() { return _mask; }
  size_t GetMaskCount() { return _mask.size(); }
  const Sprite& GetSprite() const;
  void SetStatic(const bool& _isStatic);
  const bool& IsStatic() const;
  std::vector<Crash2D::Collision> GetCollision(Instance other);
  void AddCollision(CollisionInfo collision);
  void ClearCollisions();
  float GetWidth();
  float GetHeight();

  float hSpeed = 0;
  float vSpeed = 0;

  std::vector<Mask> _mask;

  int ID = -1;

 protected:
  Object(int type = -1) : _isStatic(true) { if (type >= 0) ID = InstanceMax[type]++; }
  Sprite _sprite;
  std::vector<CollisionInfo> _collisions;
  bool _isStatic;
};

#endif
