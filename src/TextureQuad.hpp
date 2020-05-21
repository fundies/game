#ifndef TEXTUREQUAD_HPP
#define TEXTUREQUAD_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class TextureQuad {
 public:
  TextureQuad(ENGINE::Vector2<float_type> position, ENGINE::Vector2<float_type> size);
  const ENGINE::Vector2<float_type>& GetPosition() const;
  const ENGINE::Vector2<float_type>& GetSize() const;

 protected:
  ENGINE::Vector2<float_type> _position;
  ENGINE::Vector2<float_type> _size;
};

#endif
