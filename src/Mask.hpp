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
  bool LoadXML(const char* xmlFile);
  const std::shared_ptr<Crash2D::Shape>& GetShape() const;
  void SetTranslation(const Vec2f& t);
  void Translate(const Vec2f& t);
  void SetScale(const Vec2f& s);
  void SetPivot(const Vec2f& p);
  void SetRotation(const float r);
  void Transform();
  const Crash2D::Collision GetCollision(const Mask& mask, Vec2f aV,
                                        Vec2f bV) const;

  float Top = -std::numeric_limits<float>::infinity();
  float Bottom = std::numeric_limits<float>::infinity();
  float Left = -std::numeric_limits<float>::infinity();
  float Right = std::numeric_limits<float>::infinity();
  bool IsCircle = false;
  
  float Width() { return Right - Left; }
  float Height() { return Bottom - Top; }
  
 protected:
  std::shared_ptr<Crash2D::Shape> _shape;
  Crash2D::Transformation transform;
};

#endif
