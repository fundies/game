#ifndef COLOR_HPP
#define COLOR_HPP

#include "Types.hpp"

class Color {
 public:
  Color(GLubyte Red = 255, GLubyte Green = 255, GLubyte Blue = 255, GLubyte Alpha = 255);
  
  static Color Red() { return Color(255, 0, 0, 255); }

  GLubyte RedVal;
  GLubyte GreenVal;
  GLubyte BlueVal;
  GLubyte AlphaVal;

  bool operator==(const Color& right) const;
  bool operator!=(const Color& right) const;
  Color operator+(const Color& right) const;
  Color operator-(const Color& right) const;
  Color operator*(const Color& right) const;
  Color& operator+=(const Color& right);
  Color& operator-=(const Color& right);
  Color& operator*=(const Color& right);
};

#endif
