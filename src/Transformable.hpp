#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "Transformation.hpp"

class Transformable {
 public:
  const Vec2f &GetScale() const;
  void SetScale(const Vec2f &s);
  void Scale(const Vec2f &s);
  const Vec2f &GetPivot() const;
  void SetPivot(const Vec2f &p);
  const float &GetRotation() const;
  void SetRotation(const float &r);
  void Rotate(const float &r);
  const Vec2f &GetTranslation() const;
  void SetTranslation(const Vec2f &t);
  void Translate(const Vec2f &t);
  Transformation<float> GetTransform();

 protected:
  Transformation<float> _transform;
};

#endif
