#include "Vertex.hpp"

Vertex::Vertex(const Vec2f& Pos, const Vec2f& TexPos, const Color& Col)
    : _position(Pos), _texturePos(TexPos), _color(Col) {}

void Vertex::SetColor(const Color& _color) { this->_color = _color; }

void Vertex::SetPosition(const Vec2f& _position) { this->_position = _position; }

void Vertex::SetTexturePos(const Vec2f& _texturePos) { this->_texturePos = _texturePos; }

const Color& Vertex::GetColor() const { return _color; }

const Vec2f& Vertex::GetPosition() const { return _position; }

const Vec2f& Vertex::GetTexturePosition() const { return _texturePos; }

Vec2f& Vertex::GetTexturePositionM() { return _texturePos; }
