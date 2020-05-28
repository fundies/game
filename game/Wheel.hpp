#ifndef WHEEL_HPP
#define WHEEL_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Transformable.hpp"

class Wheel : public Transformable {
 public:
  Wheel();
  void SetInnerRadius(const unsigned& _innerRadius);
  void SetNumberSlices(const unsigned& _numberSlices);
  void SetSpinnerPosition(const float& _spinnerPosition);
  void SetSpinnerSpeed(const float& _spinnerSpeed);
  void SetStopSpeed(const float& _stopSpeed);
  void SetStopperSprite(const Sprite& _stopperSprite);
  void SetWheelSprite(const Sprite& _wheelSprite);
  const unsigned& GetInnerRadius() const;
  const unsigned& GetNumberSlices() const;
  const unsigned GetSpinnerPosition() const;
  const float& GetSpinnerSpeed() const;
  const float& GetStopSpeed() const;
  const Sprite& GetStopperSprite() const;
  const Sprite& GetWheelSprite() const;
  void Update(float dt);
  void Draw(BatchRenderer* renderer);
  void SetColor(const Color& color);
  void SetStopped(const bool& _stopped);
  const bool& GetStopped() const;

 protected:
  Sprite _wheelSprite;
  Sprite _stopperSprite;
  unsigned _innerRadius;
  unsigned _numberSlices;
  float _spinnerPosition;
  float _spinnerSpeed;
  float _stopSpeed;
  bool _stopped;
  int _direction;

  std::vector<ConvexShape> _lines;
};

#endif
