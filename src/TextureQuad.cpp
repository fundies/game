#include "TextureQuad.hpp"

TextureQuad::TextureQuad(Vec2f position, Vec2f size)
    : _position(position), _size(size) {}

const Vec2f& TextureQuad::GetPosition() const { return _position; }

const Vec2f& TextureQuad::GetSize() const { return _size; }
