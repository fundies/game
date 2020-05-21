#ifndef COLOR_HPP
#define COLOR_HPP

#include "Types.hpp"

class Color {
 public:
  Color(GLubyte Red = 255, GLubyte Green = 255, GLubyte Blue = 255, GLubyte Alpha = 255);

  GLubyte Red;
  GLubyte Green;
  GLubyte Blue;
  GLubyte Alpha;

  bool_t operator==(const Color& right) const;
  bool_t operator!=(const Color& right) const;
  Color operator+(const Color& right) const;
  Color operator-(const Color& right) const;
  Color operator*(const Color& right) const;
  Color& operator+=(const Color& right);
  Color& operator-=(const Color& right);
  Color& operator*=(const Color& right);
};

#endif
