#include "Transformable.hpp"

Transformation<float_type> Transformable::GetTransform() { return _transform; }

const ENGINE::Vector2<float_type> &Transformable::GetScale() const { return _transform.GetScale(); }

void Transformable::SetScale(const ENGINE::Vector2<float_type> &s) { _transform.SetScale(s); }

void Transformable::Scale(const ENGINE::Vector2<float_type> &s) { _transform.Scale(s); }

const ENGINE::Vector2<float_type> &Transformable::GetPivot() const { return _transform.GetPivot(); }

void Transformable::SetPivot(const ENGINE::Vector2<float_type> &p) { _transform.SetPivot(p); }

const float_type &Transformable::GetRotation() const { return _transform.GetRotation(); }

void Transformable::SetRotation(const float_type &r) { _transform.SetRotation(r); }

void Transformable::Rotate(const float_type &r) { _transform.Rotate(r); }

const ENGINE::Vector2<float_type> &Transformable::GetTranslation() const { return _transform.GetTranslation(); }

void Transformable::SetTranslation(const ENGINE::Vector2<float_type> &t) { return _transform.SetTranslation(t); }

void Transformable::Translate(const ENGINE::Vector2<float_type> &t) { _transform.Translate(t); }
