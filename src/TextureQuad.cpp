#include "TextureQuad.hpp"

TextureQuad::TextureQuad(ENGINE::Vector2<float_type> position, ENGINE::Vector2<float_type> size)
    : _position(position), _size(size) {}

const ENGINE::Vector2<float_type>& TextureQuad::GetPosition() const { return _position; }

const ENGINE::Vector2<float_type>& TextureQuad::GetSize() const { return _size; }
