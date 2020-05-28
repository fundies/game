#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class Texture2D {
 public:
  Texture2D();
  bool LoadImage(const char* imageFile, bool hasAlpha);
  void Bind() const;
  const unsigned& GetID() const;
  const Vec2u& GetSize() const;

 protected:
  unsigned _ID;
  Vec2u _size;
};

#endif
