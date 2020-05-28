#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include "Types.hpp"

namespace ENGINE {

template <typename T>
class Vector2 {
 public:
  T x; /*!< The x coordinate of this vector. */
  T y; /*!< The y coordinate of this vector. */

  //! Constructs a default two-dimensional vector whose coordinates are initialized to zero.
  /*!
	*/
  Vector2() : x(0), y(0) {}

  template <typename V>
  Vector2(const ENGINE::Vector2<V> &vec) {
    x = vec.x;
    y = vec.y;
  }

  //! Constructs a two-dimensional vector.
  /*!
		\param x The x coordinate of the vector.
		\param y The y coordinate of the vector.
	*/
  Vector2(const T x, const T y) : x(x), y(y) {}

  const Vector2 Perpendicular() const { return ENGINE::Vector2<T>(y, -x); }

  //! Calculates the dot product of this vector with the given vector and returns the result.
  /*!
		\param v The vector to compute the dot product of this vector.
		\return The dot product of this vector with the given vector.
	*/
  const T Dot(const Vector2 &v) const { return (x * v.x) + (y * v.y); }

  //! Calculates the cross product of this vector with the given vector and returns the result.
  /*!
		\param v The vector to compute the cross product of this vector.
		\return The cross product of this vector with the given vector.
	*/
  const T Cross(const Vector2 &v) const { return (x * v.y) - (y * v.x); }

  //! Calculates the squared length of this vector and returns the result.
  /*!
		\return The squared length of this vector.
	*/
  const T LengthSq() const { return Dot(*this); }

  //! Calculates the length or magnitude of this vector and returns the result.
  /*!
		\return The length of this vector.
	*/
  const T Length() const { return std::sqrt(LengthSq()); }

  //! Calculates the distance between this vector and the given vector and returns the result.
  /*!
		\param v The vector to compute the distance of this vector.
		\return The distance between this vector and the given vector.
	*/
  const T GetDistance(const Vector2 &v) const {
    const ENGINE::Vector2<T> d = *this - v;
    return d.Length();
  }

  //! Calculates the normal of this vector and returns the result.
  /*!
		\return The normal of this vector.
	*/
  const Vector2 Normalize() const { return *this / Length(); }

  inline Vector2 &operator=(const Vector2 &v) {
    x = v.x;
    y = v.y;
    return *this;
  }
  inline Vector2 &operator=(const T &f) {
    x = f;
    y = f;
    return *this;
  }
  inline const Vector2 operator-(void) const { return Vector2(-x, -y); }
  inline bool operator==(const Vector2 &v) const { return (AreEqual(x, v.x) && AreEqual(y, v.y)); }
  inline bool operator!=(const Vector2 &v) const { return (x != v.x) || (y != v.y); }

  //VECTOR2 TO VECTOR2 OPERATIONS
  inline const Vector2 operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); }
  inline const Vector2 operator-(const Vector2 &v) const { return Vector2(x - v.x, y - v.y); }
  inline const Vector2 operator*(const Vector2 &v) const { return Vector2(x * v.x, y * v.y); }
  inline const Vector2 operator/(const Vector2 &v) const { return Vector2(x / v.x, y / v.y); }

  //VECTOR2 TO THIS OPERATIONS
  inline Vector2 &operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  inline Vector2 &operator-=(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  inline Vector2 &operator*=(const Vector2 &v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  inline Vector2 &operator/=(const Vector2 &v) {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  //SCALER TO VECTOR2 OPERATIONS
  inline const Vector2 operator+(T v) const { return Vector2(x + v, y + v); }
  inline const Vector2 operator-(T v) const { return Vector2(x - v, y - v); }
  inline const Vector2 operator*(T v) const { return Vector2(x * v, y * v); }
  inline const Vector2 operator/(T v) const { return Vector2(x / v, y / v); }

  //SCALER TO THIS OPERATIONS
  inline Vector2 &operator+=(T v) {
    x += v;
    y += v;
    return *this;
  }
  inline Vector2 &operator-=(T v) {
    x -= v;
    y -= v;
    return *this;
  }
  inline Vector2 &operator*=(T v) {
    x *= v;
    y *= v;
    return *this;
  }
  inline Vector2 &operator/=(T v) {
    x /= v;
    y /= v;
    return *this;
  }
  bool operator<(const Vector2 &rhs) const { return ((x << 16 | y) < (rhs.x << 16 | rhs.y)); }

 private:
  bool AreEqual(T a, T b) const {
    //change 0.1 to real precision
    return (a == b || std::fabs(a - b) <= 0.1);
  }
};

}  // namespace ENGINE

using Vec2f = ENGINE::Vector2<float>;
using Vec2i = ENGINE::Vector2<int>;
using Vec2u = ENGINE::Vector2<unsigned>;

#endif
