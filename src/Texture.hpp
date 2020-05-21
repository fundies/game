#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class Texture2D {
 public:
  Texture2D();
  bool_t LoadImage(const char_t* imageFile, bool_t hasAlpha);
  void Bind() const;
  const uint_t& GetID() const;
  const ENGINE::Vector2<uint_t>& GetSize() const;

 protected:
  uint_t _ID;
  ENGINE::Vector2<uint_t> _size;
};

#endif
