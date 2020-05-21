#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Vector2.hpp"

//!  A class representing a 2D Transformation */
template <class T>
class Transformation {
 public:
  //! Constructs a default transformation.
  /*!
		The transformations must be set manually.
	*/
  Transformation()
      : _scale(ENGINE::Vector2<T>(1, 1)),
        _rotation(0),
        _translation(ENGINE::Vector2<T>(0, 0)),
        _pivot(ENGINE::Vector2<T>(0, 0)) {}

  //! Constructs a transformation with a given scale, radius and translation
  /*!
		\param s The tranformation's scale.
		\param r The tranformation's rotation.
		\param t The tranformation's translation.
	*/
  Transformation(const T &s, const T &r, const ENGINE::Vector2<T> &t)
      : _scale(s), _rotation(r), _translation(t), _pivot(ENGINE::Vector2<T>(0, 0)) {}

  //! Gets the scale of this transformation.
  /*!
		\return The scale of this transformation.
	*/
  const ENGINE::Vector2<T> &GetScale() const { return _scale; }

  //! Sets the scale of this transformation.
  /*!
		\param s The new scale of the transformation.
	*/
  void SetScale(const ENGINE::Vector2<T> &s) { _scale = s; }

  //! Applies a value to the current scale of this transformation.
  /*!
		\param s The value to apply to the scale of the transformation.
	*/
  void Scale(const ENGINE::Vector2<T> &s) { _scale *= s; }

  //! Gets the pivot point_t used for rotation.
  /*!
		\return The rotation of this transformation.
	*/
  const ENGINE::Vector2<T> &GetPivot() const { return _pivot; }

  //! Sets the pivot point_t used for rotation.
  /*!
		\param p The new pivot point_t used for rotation..
	*/
  void SetPivot(const ENGINE::Vector2<T> &p) { _pivot = p; }

  //! Gets the rotation of this transformation.
  /*!
		\return The rotation of this transformation.
	*/
  const T &GetRotation() const { return _rotation; }

  //! Sets the rotation of this transformation.
  /*!
		\param r The new rotation of the transformation.
	*/
  void SetRotation(const T &r) {
    _rotation = r;

    _rotation = std::fmod(_rotation, 360.0);

    if (_rotation < 0) _rotation += 360;
  }

  //! Applies a value to the current rotation of this transformation.
  /*!
		\param r The value to apply to the rotation of the transformation.
	*/
  void Rotate(const T &r) {
    _rotation += r;

    _rotation = std::fmod(_rotation, 360.0);

    if (_rotation < 0) _rotation += 360;
  }

  //! Gets the translation of this transformation.
  /*!
		\return The translation of this transformation.
	*/
  const ENGINE::Vector2<T> &GetTranslation() const { return _translation; }

  //! Sets the translation of this transformation.
  /*!
		\param t The new translation of the transformation.
	*/
  void SetTranslation(const ENGINE::Vector2<T> &t) { _translation = t; }

  //! Applies a value to the current translation of this transformation.
  /*!
		\param t The value to apply to the translation of the transformation.
	*/
  void Translate(const ENGINE::Vector2<T> &t) { _translation += t; }

  //! Negate Operator override,
  /*!
	*/
  const Transformation operator-(void) const { return Transformation<T>(-_scale, -_rotation, -_translation); }

 protected:
  ENGINE::Vector2<T> _scale;       /*!< The scale of the transformation. */
  T _rotation;                     /*!< The rotation of the transformation. */
  ENGINE::Vector2<T> _translation; /*!< The translation of the transformation. */
  ENGINE::Vector2<T> _pivot;       /*!< The pivot point_t used for rotation of the transformation. */
};

#endif
