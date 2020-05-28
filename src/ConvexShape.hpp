#ifndef CONVEXSHAPE_HPP
#define CONVEXSHAPE_HPP

#include "Transformable.hpp"
#include "Vertex.hpp"

#include <vector>

class ConvexShape : public Transformable {
 public:
  ConvexShape(unsigned vertexCount);

  void AddPoint(Vertex vertex);
  void SetPoint(unsigned index, const Vertex& vertex);

  void SetPointPosition(unsigned index, const Vec2f& pos);
  void SetPointTexturePosition(unsigned index, const Vec2f& pos);
  void SetPointColor(unsigned index, const Color& color);

  void SetColor(const Color& color);

  const Vertex& GetPoint(unsigned index) const;
  Vertex& GetPointM(unsigned index);
  void SetPointCount(unsigned vertexCount);
  const unsigned GetPointCount() const;

  const std::vector<Vertex>& GetVerts() const;

  void CalcCenter();
  bool AABB(ConvexShape& shape);

  const float& GetBottom() const;
  const Vec2f& GetCenter() const;
  const float& GetLeft() const;
  const float& GetRight() const;
  const float& GetTop() const;
  const float GetWidth() const;
  const float GetHeight() const;

  const Vec2f GetTransformedPoint(unsigned index) const;
  const Vec2f GetTransformedCenter() const;

 protected:
  std::vector<Vertex> _verts;
  Vec2f _center;
  float _top;
  float _left;
  float _bottom;
  float _right;
};

#endif
