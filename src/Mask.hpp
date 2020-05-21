#ifndef MASK_HPP
#define MASK_HPP

#include "Transformable.hpp"
#include "Types.hpp"
#include "XMLParser.hpp"

#include <Crash2D/Crash2D.hpp>

class Mask : public Transformable {
 public:
  Mask();
  Mask(const Mask& mask);
  bool_t LoadXML(const char_t* xmlFile);
  const std::shared_ptr<Crash2D::Shape>& GetShape() const;
  void SetTranslation(const ENGINE::Vector2<float_type>& t);
  void Translate(const ENGINE::Vector2<float_type>& t);
  void SetScale(const ENGINE::Vector2<float_type>& s);
  void SetPivot(const ENGINE::Vector2<float_type>& p);
  void SetRotation(const float_type r);
  void Transform();
  const Crash2D::Collision GetCollision(const Mask& mask, ENGINE::Vector2<float_type> aV,
                                        ENGINE::Vector2<float_type> bV) const;

  float Top = -std::numeric_limits<float>::infinity();
  float Bottom = std::numeric_limits<float>::infinity();
  float Left = -std::numeric_limits<float>::infinity();
  float Right = std::numeric_limits<float>::infinity();

 protected:
  std::shared_ptr<Crash2D::Shape> _shape;
  Crash2D::Transformation transform;
};

#endif
