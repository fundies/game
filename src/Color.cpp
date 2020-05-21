#include "Color.hpp"

#include <algorithm>

Color::Color(GLubyte Red, GLubyte Green, GLubyte Blue, GLubyte Alpha)
    : Red(Red), Green(Green), Blue(Blue), Alpha(Alpha) {}

bool_t Color::operator==(const Color& right) const {
  return (this->Red == right.Red) && (this->Green == right.Green) && (this->Blue == right.Blue) &&
         (this->Alpha == right.Alpha);
}

bool_t Color::operator!=(const Color& right) const { return !(*this == right); }

Color Color::operator+(const Color& right) const {
  return Color(
      GLubyte(std::min(int_t(this->Red) + right.Red, 255)), GLubyte(std::min(int_t(this->Green) + right.Green, 255)),
      GLubyte(std::min(int_t(this->Blue) + right.Blue, 255)), GLubyte(std::min(int_t(this->Alpha) + right.Alpha, 255)));
}

Color Color::operator-(const Color& right) const {
  return Color(
      GLubyte(std::max(int_t(this->Red) - right.Red, 0)), GLubyte(std::max(int_t(this->Green) - right.Green, 0)),
      GLubyte(std::max(int_t(this->Blue) - right.Blue, 0)), GLubyte(std::max(int_t(this->Alpha) - right.Alpha, 0)));
}

Color Color::operator*(const Color& right) const {
  return Color(GLubyte(int_t(this->Red) * right.Red / 255), GLubyte(int_t(this->Green) * right.Green / 255),
               GLubyte(int_t(this->Blue) * right.Blue / 255), GLubyte(int_t(this->Alpha) * right.Alpha / 255));
}

Color& Color::operator+=(const Color& right) {
  Color temp = Color(
      GLubyte(std::min(int_t(this->Red) + right.Red, 255)), GLubyte(std::min(int_t(this->Green) + right.Green, 255)),
      GLubyte(std::min(int_t(this->Blue) + right.Blue, 255)), GLubyte(std::min(int_t(this->Alpha) + right.Alpha, 255)));

  this->Red = temp.Red;
  this->Green = temp.Green;
  this->Blue = temp.Blue;
  this->Alpha = temp.Alpha;

  return *this;
}

Color& Color::operator-=(const Color& right) {
  Color temp = Color(
      GLubyte(std::max(int_t(this->Red) - right.Red, 0)), GLubyte(std::max(int_t(this->Green) - right.Green, 0)),
      GLubyte(std::max(int_t(this->Blue) - right.Blue, 0)), GLubyte(std::max(int_t(this->Alpha) - right.Alpha, 0)));

  this->Red = temp.Red;
  this->Green = temp.Green;
  this->Blue = temp.Blue;
  this->Alpha = temp.Alpha;

  return *this;
}

Color& Color::operator*=(const Color& right) {
  Color temp = Color(GLubyte(int_t(this->Red) * right.Red / 255), GLubyte(int_t(this->Green) * right.Green / 255),
                     GLubyte(int_t(this->Blue) * right.Blue / 255), GLubyte(int_t(this->Alpha) * right.Alpha / 255));

  this->Red = temp.Red;
  this->Green = temp.Green;
  this->Blue = temp.Blue;
  this->Alpha = temp.Alpha;

  return *this;
}
