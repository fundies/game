#include "Drawable.hpp"

Drawable::Drawable(std::initializer_list<Vertex> verticies, Transformation<float> transform)
    : _vertices(verticies)  //, _transform(transform), _texture(texture)
{}

Vertex& Drawable::GetCenter() { return _center; }

void Drawable::SetCenter(Vertex center) { _center = center; }

Vertex& Drawable::GetVertex(unsigned index) { return _vertices[index]; }

void Drawable::SetVertex(unsigned index, Vertex vertex) { _vertices[index] = vertex; }

unsigned Drawable::GetVertexCount() { return _vertices.size(); }

void Drawable::SetVertexCount(unsigned count) { _vertices.resize(count); }

//Texture2D& Drawable::GetTexture();
//void Drawable::SetTexture(Texture2D& texture);

//Transform& Drawable::GetTransform();
//void Drawable::SetTransform(Transform transform);
