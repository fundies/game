#include "Transformable.hpp"

Transformation<float> Transformable::GetTransform() { return _transform; }

const Vec2f &Transformable::GetScale() const { return _transform.GetScale(); }

void Transformable::SetScale(const Vec2f &s) { _transform.SetScale(s); }

void Transformable::Scale(const Vec2f &s) { _transform.Scale(s); }

const Vec2f &Transformable::GetPivot() const { return _transform.GetPivot(); }

void Transformable::SetPivot(const Vec2f &p) { _transform.SetPivot(p); }

const float &Transformable::GetRotation() const { return _transform.GetRotation(); }

void Transformable::SetRotation(const float &r) { _transform.SetRotation(r); }

void Transformable::Rotate(const float &r) { _transform.Rotate(r); }

const Vec2f &Transformable::GetTranslation() const { return _transform.GetTranslation(); }

void Transformable::SetTranslation(const Vec2f &t) { return _transform.SetTranslation(t); }

void Transformable::Translate(const Vec2f &t) { _transform.Translate(t); }
