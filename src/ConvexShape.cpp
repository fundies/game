#include "ConvexShape.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>

ConvexShape::ConvexShape(unsigned vertexCount)
    : _verts(vertexCount),
      _top(std::numeric_limits<float>::max()),
      _left(std::numeric_limits<float>::max()),
      _bottom(std::numeric_limits<float>::min()),
      _right(std::numeric_limits<float>::min()) {}

void ConvexShape::AddPoint(Vertex vertex) {
  _top = std::min(_top, vertex.GetPosition().y);
  _left = std::min(_left, vertex.GetPosition().x);

  _bottom = std::max(_bottom, vertex.GetPosition().y);
  _right = std::max(_right, vertex.GetPosition().x);

  _verts.push_back(vertex);
}

void ConvexShape::SetPointPosition(unsigned index, const Vec2f& pos) {
  _top = std::min(_top, pos.y);
  _left = std::min(_left, pos.x);

  _bottom = std::max(_bottom, pos.y);
  _right = std::max(_right, pos.x);
  _verts[index].SetPosition(pos);
}

void ConvexShape::SetPointTexturePosition(unsigned index, const Vec2f& pos) {
  _verts[index].SetTexturePos(pos);
}

void ConvexShape::SetPointColor(unsigned index, const Color& color) { _verts[index].SetColor(color); }

void ConvexShape::SetPoint(unsigned index, const Vertex& vertex) {
  _top = std::min(_top, vertex.GetPosition().y);
  _left = std::min(_left, vertex.GetPosition().x);

  _bottom = std::max(_bottom, vertex.GetPosition().y);
  _right = std::max(_right, vertex.GetPosition().x);

  _verts[0] = vertex;
}

const Vertex& ConvexShape::GetPoint(unsigned index) const { return _verts[index]; }

Vertex& ConvexShape::GetPointM(unsigned index) { return _verts[index]; }

void ConvexShape::SetPointCount(unsigned vertexCount) { _verts.resize(vertexCount); }

const unsigned ConvexShape::GetPointCount() const { return _verts.size(); }

const std::vector<Vertex>& ConvexShape::GetVerts() const { return _verts; }

void ConvexShape::CalcCenter() {
  _center = Vec2f(0, 0);

  for (unsigned i = 0; i < _verts.size(); i++) _center += _verts[i].GetPosition();

  _center = Vec2f(_center.x / _verts.size(), _center.y / _verts.size());
}

bool ConvexShape::AABB(ConvexShape& shape) {
  if (shape._right < _left || shape._left > _right) return false;

  if (shape._bottom < _top || shape._top > _bottom) return false;

  return true;
}

const float& ConvexShape::GetBottom() const { return _bottom; }
const Vec2f& ConvexShape::GetCenter() const { return _center; }
const float& ConvexShape::GetLeft() const { return _left; }
const float& ConvexShape::GetRight() const { return _right; }
const float& ConvexShape::GetTop() const { return _top; }

const float ConvexShape::GetWidth() const { return std::abs(_right - _left); }

const float ConvexShape::GetHeight() const { return std::abs(_bottom - _top); }

void ConvexShape::SetColor(const Color& color) {
  for (auto& vert : _verts) {
    vert.SetColor(color);
  }
}

const Vec2f ConvexShape::GetTransformedPoint(unsigned index) const {
  Vec2f pt = GetPoint(index).GetPosition();

  // Scale
  pt -= _transform.GetPivot();
  pt *= _transform.GetScale();
  pt += _transform.GetPivot();

  // Rotate
  const float radians = (_transform.GetRotation() * M_PI) / 180;
  const float s = std::sin(radians);
  const float c = std::cos(radians);

  Vec2f p = pt - _transform.GetPivot();

  const float nx = (p.x * c) - (p.y * s);
  const float ny = (p.x * s) + (p.y * c);

  p = Vec2f(nx, ny) + _transform.GetPivot();

  // Translate
  p += _transform.GetTranslation();

  return p;
}

const Vec2f ConvexShape::GetTransformedCenter() const {
  Vec2f pt = GetCenter();

  // Scale
  pt -= _transform.GetPivot();
  pt *= _transform.GetScale();
  pt += _transform.GetPivot();

  // Rotate
  const float radians = (_transform.GetRotation() * M_PI) / 180;
  const float s = std::sin(radians);
  const float c = std::cos(radians);

  Vec2f p = pt - _transform.GetPivot();

  const float nx = (p.x * c) - (p.y * s);
  const float ny = (p.x * s) + (p.y * c);

  p = Vec2f(nx, ny) + _transform.GetPivot();

  // Translate
  p += _transform.GetTranslation();

  return p;
}
