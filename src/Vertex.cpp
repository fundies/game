#include "Vertex.hpp"

Vertex::Vertex(const ENGINE::Vector2<float_type>& Pos, const ENGINE::Vector2<float_type>& TexPos, const Color& Col)
    : _position(Pos), _texturePos(TexPos), _color(Col) {}

void Vertex::SetColor(const Color& _color) { this->_color = _color; }

void Vertex::SetPosition(const ENGINE::Vector2<float_type>& _position) { this->_position = _position; }

void Vertex::SetTexturePos(const ENGINE::Vector2<float_type>& _texturePos) { this->_texturePos = _texturePos; }

const Color& Vertex::GetColor() const { return _color; }

const ENGINE::Vector2<float_type>& Vertex::GetPosition() const { return _position; }

const ENGINE::Vector2<float_type>& Vertex::GetTexturePosition() const { return _texturePos; }

ENGINE::Vector2<float_type>& Vertex::GetTexturePositionM() { return _texturePos; }
