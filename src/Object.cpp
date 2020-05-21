#include "Object.hpp"

void Object::SetMask(const Mask& _mask) { this->_mask = _mask; }

void Object::SetSprite(const Sprite& _sprite) { this->_sprite = _sprite; }

Mask& Object::GetMask() { return _mask; }

const Sprite& Object::GetSprite() const { return _sprite; }

void Object::Draw(BatchRenderer* _renderer, View& view) {
  _sprite.SetTranslation(GetTranslation());
  _sprite.SetScale(GetScale());
  _sprite.SetPivot(GetPivot());
  _sprite.SetRotation(GetRotation());

  _renderer->DrawSprite(_sprite, view);

  if (_mask.GetShape() != nullptr) {
    uint_t pointCount = _mask.GetShape()->GetPointCount();
    ConvexShape m(pointCount);

    for (uint_t point = 0; point < pointCount; point++) {
      Crash2D::Vector2 pt = _mask.GetShape()->GetPoint(point);
      m.SetPointPosition(point, ENGINE::Vector2<float_type>(pt.x, pt.y));
    }

    m.SetColor(Color(255, 0, 0, 100));

    //_renderer->DrawConvexShape(m, view);
  }
}

void Object::SetStatic(const bool_t& _isStatic) { this->_isStatic = _isStatic; }

const bool_t& Object::IsStatic() const { return _isStatic; }

Crash2D::Collision Object::GetCollision(Instance other) {
  return GetMask().GetCollision(other->GetMask(), ENGINE::Vector2<float_type>(hSpeed, vSpeed),
                                ENGINE::Vector2<float_type>(other->hSpeed, other->vSpeed));
}

void Object::AddCollision(CollisionInfo collision) { _collisions.push_back(collision); }

void Object::ClearCollisions() { _collisions.clear(); }
