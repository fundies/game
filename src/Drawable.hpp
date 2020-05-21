#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "Texture.hpp"
#include "Transformation.hpp"
#include "Vertex.hpp"

#include <initializer_list>
#include <vector>

class Drawable {
 public:
  Drawable(std::initializer_list<Vertex> verticies = {},
           Transformation<float_type> transform = Transformation<float_type>());

  Vertex& GetCenter();
  void SetCenter(Vertex center);

  Vertex& GetVertex(uint_t index);
  void SetVertex(uint_t index, Vertex vertex);

  uint_t GetVertexCount();
  void SetVertexCount(uint_t count);

  Texture2D& GetTexture();
  void SetTexture(Texture2D& texture);

  //Transform& GetTransform();
  //void SetTransform(Transform transform);

 protected:
  Vertex _center;
  vector_t<Vertex> _vertices;
  //Transform _transform;
};

#endif
