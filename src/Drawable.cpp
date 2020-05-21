#include "Drawable.hpp"

Drawable::Drawable(std::initializer_list<Vertex> verticies, Transformation<float_type> transform)
    : _vertices(verticies)  //, _transform(transform), _texture(texture)
{}

Vertex& Drawable::GetCenter() { return _center; }

void Drawable::SetCenter(Vertex center) { _center = center; }

Vertex& Drawable::GetVertex(uint_t index) { return _vertices[index]; }

void Drawable::SetVertex(uint_t index, Vertex vertex) { _vertices[index] = vertex; }

uint_t Drawable::GetVertexCount() { return _vertices.size(); }

void Drawable::SetVertexCount(uint_t count) { _vertices.resize(count); }

//Texture2D& Drawable::GetTexture();
//void Drawable::SetTexture(Texture2D& texture);

//Transform& Drawable::GetTransform();
//void Drawable::SetTransform(Transform transform);
