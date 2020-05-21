#include "ConvexShape.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>

ConvexShape::ConvexShape(uint_t vertexCount)
    : _verts(vertexCount),
      _top(std::numeric_limits<float_type>::max()),
      _left(std::numeric_limits<float_type>::max()),
      _bottom(std::numeric_limits<float_type>::min()),
      _right(std::numeric_limits<float_type>::min()) {}

void ConvexShape::AddPoint(Vertex vertex) {
  _top = std::min(_top, vertex.GetPosition().y);
  _left = std::min(_left, vertex.GetPosition().x);

  _bottom = std::max(_bottom, vertex.GetPosition().y);
  _right = std::max(_right, vertex.GetPosition().x);

  _verts.push_back(vertex);
}

void ConvexShape::SetPointPosition(uint_t index, const ENGINE::Vector2<float_type>& pos) {
  _top = std::min(_top, pos.y);
  _left = std::min(_left, pos.x);

  _bottom = std::max(_bottom, pos.y);
  _right = std::max(_right, pos.x);
  _verts[index].SetPosition(pos);
}

void ConvexShape::SetPointTexturePosition(uint_t index, const ENGINE::Vector2<float_type>& pos) {
  _verts[index].SetTexturePos(pos);
}

void ConvexShape::SetPointColor(uint_t index, const Color& color) { _verts[index].SetColor(color); }

void ConvexShape::SetPoint(uint_t index, const Vertex& vertex) {
  _top = std::min(_top, vertex.GetPosition().y);
  _left = std::min(_left, vertex.GetPosition().x);

  _bottom = std::max(_bottom, vertex.GetPosition().y);
  _right = std::max(_right, vertex.GetPosition().x);

  _verts[0] = vertex;
}

const Vertex& ConvexShape::GetPoint(uint_t index) const { return _verts[index]; }

Vertex& ConvexShape::GetPointM(uint_t index) { return _verts[index]; }

void ConvexShape::SetPointCount(uint_t vertexCount) { _verts.resize(vertexCount); }

const uint_t ConvexShape::GetPointCount() const { return _verts.size(); }

const vector_t<Vertex>& ConvexShape::GetVerts() const { return _verts; }

void ConvexShape::CalcCenter() {
  _center = ENGINE::Vector2<float_type>(0, 0);

  for (uint_t i = 0; i < _verts.size(); i++) _center += _verts[i].GetPosition();

  _center = ENGINE::Vector2<float_type>(_center.x / _verts.size(), _center.y / _verts.size());
}

bool_t ConvexShape::AABB(ConvexShape& shape) {
  if (shape._right < _left || shape._left > _right) return false;

  if (shape._bottom < _top || shape._top > _bottom) return false;

  return true;
}

const float_type& ConvexShape::GetBottom() const { return _bottom; }
const ENGINE::Vector2<float_type>& ConvexShape::GetCenter() const { return _center; }
const float_type& ConvexShape::GetLeft() const { return _left; }
const float_type& ConvexShape::GetRight() const { return _right; }
const float_type& ConvexShape::GetTop() const { return _top; }

const float_type ConvexShape::GetWidth() const { return std::abs(_right - _left); }

const float_type ConvexShape::GetHeight() const { return std::abs(_bottom - _top); }

void ConvexShape::SetColor(const Color& color) {
  for (auto& vert : _verts) {
    vert.SetColor(color);
  }
}

const ENGINE::Vector2<float_type> ConvexShape::GetTransformedPoint(uint_t index) const {
  ENGINE::Vector2<float_type> pt = GetPoint(index).GetPosition();

  // Scale
  pt -= _transform.GetPivot();
  pt *= _transform.GetScale();
  pt += _transform.GetPivot();

  // Rotate
  const float_type radians = (_transform.GetRotation() * M_PI) / 180;
  const float_type s = std::sin(radians);
  const float_type c = std::cos(radians);

  ENGINE::Vector2<float_type> p = pt - _transform.GetPivot();

  const float_type nx = (p.x * c) - (p.y * s);
  const float_type ny = (p.x * s) + (p.y * c);

  p = ENGINE::Vector2<float_type>(nx, ny) + _transform.GetPivot();

  // Translate
  p += _transform.GetTranslation();

  return p;
}

const ENGINE::Vector2<float_type> ConvexShape::GetTransformedCenter() const {
  ENGINE::Vector2<float_type> pt = GetCenter();

  // Scale
  pt -= _transform.GetPivot();
  pt *= _transform.GetScale();
  pt += _transform.GetPivot();

  // Rotate
  const float_type radians = (_transform.GetRotation() * M_PI) / 180;
  const float_type s = std::sin(radians);
  const float_type c = std::cos(radians);

  ENGINE::Vector2<float_type> p = pt - _transform.GetPivot();

  const float_type nx = (p.x * c) - (p.y * s);
  const float_type ny = (p.x * s) + (p.y * c);

  p = ENGINE::Vector2<float_type>(nx, ny) + _transform.GetPivot();

  // Translate
  p += _transform.GetTranslation();

  return p;
}
