#ifndef CONVEXSHAPE_HPP
#define CONVEXSHAPE_HPP

#include "Transformable.hpp"
#include "Vertex.hpp"

#include <vector>

class ConvexShape : public Transformable {
 public:
  ConvexShape(uint_t vertexCount);

  void AddPoint(Vertex vertex);
  void SetPoint(uint_t index, const Vertex& vertex);

  void SetPointPosition(uint_t index, const ENGINE::Vector2<float_type>& pos);
  void SetPointTexturePosition(uint_t index, const ENGINE::Vector2<float_type>& pos);
  void SetPointColor(uint_t index, const Color& color);

  void SetColor(const Color& color);

  const Vertex& GetPoint(uint_t index) const;
  Vertex& GetPointM(uint_t index);
  void SetPointCount(uint_t vertexCount);
  const uint_t GetPointCount() const;

  const vector_t<Vertex>& GetVerts() const;

  void CalcCenter();
  bool_t AABB(ConvexShape& shape);

  const float_type& GetBottom() const;
  const ENGINE::Vector2<float_type>& GetCenter() const;
  const float_type& GetLeft() const;
  const float_type& GetRight() const;
  const float_type& GetTop() const;
  const float_type GetWidth() const;
  const float_type GetHeight() const;

  const ENGINE::Vector2<float_type> GetTransformedPoint(uint_t index) const;
  const ENGINE::Vector2<float_type> GetTransformedCenter() const;

 protected:
  vector_t<Vertex> _verts;
  ENGINE::Vector2<float_type> _center;
  float_type _top;
  float_type _left;
  float_type _bottom;
  float_type _right;
};

#endif
