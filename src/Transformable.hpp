#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "Transformation.hpp"

class Transformable {
 public:
  const ENGINE::Vector2<float_type> &GetScale() const;
  void SetScale(const ENGINE::Vector2<float_type> &s);
  void Scale(const ENGINE::Vector2<float_type> &s);
  const ENGINE::Vector2<float_type> &GetPivot() const;
  void SetPivot(const ENGINE::Vector2<float_type> &p);
  const float_type &GetRotation() const;
  void SetRotation(const float_type &r);
  void Rotate(const float_type &r);
  const ENGINE::Vector2<float_type> &GetTranslation() const;
  void SetTranslation(const ENGINE::Vector2<float_type> &t);
  void Translate(const ENGINE::Vector2<float_type> &t);
  Transformation<float_type> GetTransform();

 protected:
  Transformation<float_type> _transform;
};

#endif
