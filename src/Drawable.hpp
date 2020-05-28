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
           Transformation<float> transform = Transformation<float>());

  Vertex& GetCenter();
  void SetCenter(Vertex center);

  Vertex& GetVertex(unsigned index);
  void SetVertex(unsigned index, Vertex vertex);

  unsigned GetVertexCount();
  void SetVertexCount(unsigned count);

  Texture2D& GetTexture();
  void SetTexture(Texture2D& texture);

  //Transform& GetTransform();
  //void SetTransform(Transform transform);

 protected:
  Vertex _center;
  std::vector<Vertex> _vertices;
  //Transform _transform;
};

#endif
