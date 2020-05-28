#ifndef TEXTUREQUAD_HPP
#define TEXTUREQUAD_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class TextureQuad {
 public:
  TextureQuad(Vec2f position, Vec2f size);
  const Vec2f& GetPosition() const;
  const Vec2f& GetSize() const;

 protected:
  Vec2f _position;
  Vec2f _size;
};

#endif
