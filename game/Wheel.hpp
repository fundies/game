#ifndef WHEEL_HPP
#define WHEEL_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Transformable.hpp"
#include "View.hpp"

class Wheel : public Transformable {
 public:
  Wheel();
  void SetInnerRadius(const uint_t& _innerRadius);
  void SetNumberSlices(const uint_t& _numberSlices);
  void SetSpinnerPosition(const float_type& _spinnerPosition);
  void SetSpinnerSpeed(const float_type& _spinnerSpeed);
  void SetStopSpeed(const float_type& _stopSpeed);
  void SetStopperSprite(const Sprite& _stopperSprite);
  void SetWheelSprite(const Sprite& _wheelSprite);
  const uint_t& GetInnerRadius() const;
  const uint_t& GetNumberSlices() const;
  const uint_t GetSpinnerPosition() const;
  const float_type& GetSpinnerSpeed() const;
  const float_type& GetStopSpeed() const;
  const Sprite& GetStopperSprite() const;
  const Sprite& GetWheelSprite() const;
  void Update(float_type dt);
  void Draw(BatchRenderer* renderer, const View& view);
  void SetColor(const Color& color);
  void SetStopped(const bool_t& _stopped);
  const bool_t& GetStopped() const;

 protected:
  Sprite _wheelSprite;
  Sprite _stopperSprite;
  uint_t _innerRadius;
  uint_t _numberSlices;
  float_type _spinnerPosition;
  float_type _spinnerSpeed;
  float_type _stopSpeed;
  bool_t _stopped;
  int_t _direction;

  std::vector<ConvexShape> _lines;
};

#endif
