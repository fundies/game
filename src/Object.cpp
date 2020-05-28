#include "Object.hpp"

void Object::SetMask(int id, const Mask& _mask) { this->_mask[id] = _mask; }

void Object::SetSprite(const Sprite& _sprite) { this->_sprite = _sprite; }

Mask& Object::GetMask(int id) { return _mask[id]; }

const Sprite& Object::GetSprite() const { return _sprite; }

void Object::Draw(BatchRenderer* _renderer) {
  _sprite.SetTranslation(GetTranslation());
  _sprite.SetScale(GetScale());
  _sprite.SetPivot(GetPivot());
  _sprite.SetRotation(GetRotation());

  _renderer->DrawSprite(_sprite);

  /*for (const auto& mask : _mask) {
    if (mask.GetShape() != nullptr) {
      if (mask.IsCircle) {
        auto s = mask.GetShape();
        _renderer->DrawCircle(Vec2f(s->GetCenter().x, s->GetCenter().y), s->GetRadius(), Color(255, 0, 0, 100));
      } else {
        unsigned pointCount = mask.GetShape()->GetPointCount();
        ConvexShape m(pointCount);

        for (unsigned point = 0; point < pointCount; point++) {
          Crash2D::Vector2 pt = mask.GetShape()->GetPoint(point);
          m.SetPointPosition(point, Vec2f(pt.x, pt.y));
        }
        _renderer->DrawConvexShape(m, Color(255, 0, 0, 100));
      }
    }
  }*/
}

void Object::SetStatic(const bool& _isStatic) { this->_isStatic = _isStatic; }

const bool& Object::IsStatic() const { return _isStatic; }

std::vector<Crash2D::Collision> Object::GetCollision(Instance other) {
  std::vector<Crash2D::Collision> collisions; 
  for (auto& m1 : GetMasks()) {
    for (auto& m2 : other->GetMasks()) {
      collisions.push_back(m1.GetCollision(m2, Vec2f(hSpeed, vSpeed),
                                Vec2f(other->hSpeed, other->vSpeed)));
    }
  }
  return collisions;
}

void Object::AddCollision(CollisionInfo collision) { _collisions.push_back(collision); }

void Object::ClearCollisions() { _collisions.clear(); }

float Object::GetWidth() {
  return _sprite.GetTextureSize().x;
}

float Object::GetHeight() {
  return _sprite.GetTextureSize().y;
}
