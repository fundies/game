#include "Color.hpp"

#include <algorithm>

Color::Color(GLubyte Red, GLubyte Green, GLubyte Blue, GLubyte Alpha)
    : RedVal(Red), GreenVal(Green), BlueVal(Blue), AlphaVal(Alpha) {}

bool Color::operator==(const Color& right) const {
  return (this->RedVal == right.RedVal) && (this->GreenVal == right.GreenVal) && (this->BlueVal == right.BlueVal) &&
         (this->AlphaVal == right.AlphaVal);
}

bool Color::operator!=(const Color& right) const { return !(*this == right); }

Color Color::operator+(const Color& right) const {
  return Color(
      GLubyte(std::min(int(this->RedVal) + right.RedVal, 255)), GLubyte(std::min(int(this->GreenVal) + right.GreenVal, 255)),
      GLubyte(std::min(int(this->BlueVal) + right.BlueVal, 255)), GLubyte(std::min(int(this->AlphaVal) + right.AlphaVal, 255)));
}

Color Color::operator-(const Color& right) const {
  return Color(
      GLubyte(std::max(int(this->RedVal) - right.RedVal, 0)), GLubyte(std::max(int(this->GreenVal) - right.GreenVal, 0)),
      GLubyte(std::max(int(this->BlueVal) - right.BlueVal, 0)), GLubyte(std::max(int(this->AlphaVal) - right.AlphaVal, 0)));
}

Color Color::operator*(const Color& right) const {
  return Color(GLubyte(int(this->RedVal) * right.RedVal / 255), GLubyte(int(this->GreenVal) * right.GreenVal / 255),
               GLubyte(int(this->BlueVal) * right.BlueVal / 255), GLubyte(int(this->AlphaVal) * right.AlphaVal / 255));
}

Color& Color::operator+=(const Color& right) {
  Color temp = Color(
      GLubyte(std::min(int(this->RedVal) + right.RedVal, 255)), GLubyte(std::min(int(this->GreenVal) + right.GreenVal, 255)),
      GLubyte(std::min(int(this->BlueVal) + right.BlueVal, 255)), GLubyte(std::min(int(this->AlphaVal) + right.AlphaVal, 255)));

  this->RedVal = temp.RedVal;
  this->GreenVal = temp.GreenVal;
  this->BlueVal = temp.BlueVal;
  this->AlphaVal = temp.AlphaVal;

  return *this;
}

Color& Color::operator-=(const Color& right) {
  Color temp = Color(
      GLubyte(std::max(int(this->RedVal) - right.RedVal, 0)), GLubyte(std::max(int(this->GreenVal) - right.GreenVal, 0)),
      GLubyte(std::max(int(this->BlueVal) - right.BlueVal, 0)), GLubyte(std::max(int(this->AlphaVal) - right.AlphaVal, 0)));

  this->RedVal = temp.RedVal;
  this->GreenVal = temp.GreenVal;
  this->BlueVal = temp.BlueVal;
  this->AlphaVal = temp.AlphaVal;

  return *this;
}

Color& Color::operator*=(const Color& right) {
  Color temp = Color(GLubyte(int(this->RedVal) * right.RedVal / 255), GLubyte(int(this->GreenVal) * right.GreenVal / 255),
                     GLubyte(int(this->BlueVal) * right.BlueVal / 255), GLubyte(int(this->AlphaVal) * right.AlphaVal / 255));

  this->RedVal = temp.RedVal;
  this->GreenVal = temp.GreenVal;
  this->BlueVal = temp.BlueVal;
  this->AlphaVal = temp.AlphaVal;

  return *this;
}
