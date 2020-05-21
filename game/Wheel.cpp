#include "Wheel.hpp"

Wheel::Wheel() : _spinnerPosition(0), _spinnerSpeed(0), _stopped(false) {}

void Wheel::SetInnerRadius(const uint_t& _innerRadius) { this->_innerRadius = _innerRadius; }

void Wheel::SetNumberSlices(const uint_t& _numberSlices) {
  this->_numberSlices = _numberSlices;

  _lines.clear();

  for (unsigned c = 0; c < _numberSlices; c++) {
    int_t lineWidth = 3;

    float_type outerRadius = _wheelSprite.GetTextureSize().x / 2;

    float_type x1 = outerRadius;
    float_type y1 = outerRadius;

    float_type a = c * (360.f / _numberSlices);
    float_type y2 = _innerRadius * std::cos((a * M_PI) / 180);
    y2 += outerRadius;

    float_type x2 = _innerRadius * std::sin((a * M_PI) / 180);
    x2 += outerRadius;

    float_type dir = std::fmod(std::atan2(y1 - y2, x2 - x1) + 2 * M_PI, 2 * M_PI);
    float_type cv = std::cos(dir - M_PI / 2.0);
    float_type sv = -std::sin(dir - M_PI / 2.0);
    float_type dw = lineWidth / 2.0;

    ConvexShape line(4);
    line.SetPointPosition(0, ENGINE::Vector2<float_type>(x1 + dw * cv, y1 + dw * sv));
    line.SetPointPosition(1, ENGINE::Vector2<float_type>(x1 - dw * cv, y1 - dw * sv));
    line.SetPointPosition(2, ENGINE::Vector2<float_type>(x2 + dw * cv, y2 + dw * sv));
    line.SetPointPosition(3, ENGINE::Vector2<float_type>(x2 - dw * cv, y2 - dw * sv));

    line.SetPivot(ENGINE::Vector2<float_type>(outerRadius, outerRadius));

    _lines.push_back(line);
  }
}

void Wheel::SetSpinnerPosition(const float_type& _spinnerPosition) { this->_spinnerPosition = _spinnerPosition; }

void Wheel::SetSpinnerSpeed(const float_type& _spinnerSpeed) { this->_spinnerSpeed = _spinnerSpeed; }

void Wheel::SetStopSpeed(const float_type& _stopSpeed) { this->_stopSpeed = _stopSpeed; }

void Wheel::SetStopperSprite(const Sprite& _stopperSprite) {
  this->_stopperSprite = _stopperSprite;
  this->_stopperSprite.SetTranslation(ENGINE::Vector2<float_type>(
      (_wheelSprite.GetTextureSize().x - _stopperSprite.GetTextureSize().x) / 2, -_stopperSprite.GetTextureSize().x));
}

void Wheel::SetWheelSprite(const Sprite& _wheelSprite) { this->_wheelSprite = _wheelSprite; }

const uint_t& Wheel::GetInnerRadius() const { return _innerRadius; }

const uint_t& Wheel::GetNumberSlices() const { return _numberSlices; }

const uint_t Wheel::GetSpinnerPosition() const {
  float_type w = 360.f / _numberSlices;
  return (_numberSlices) - (_spinnerPosition / w);
}

const float_type& Wheel::GetSpinnerSpeed() const { return _spinnerSpeed; }

const float_type& Wheel::GetStopSpeed() const { return _stopSpeed; }

const Sprite& Wheel::GetStopperSprite() const { return _stopperSprite; }

const Sprite& Wheel::GetWheelSprite() const { return _wheelSprite; }

void Wheel::Update(float_type dt) {
  if (_stopped) {
    _spinnerSpeed -= _direction * _stopSpeed * dt;

    if (_direction == 1 && _spinnerSpeed < 0) _spinnerSpeed = 0;

    if (_direction == -1 && _spinnerSpeed > 0) _spinnerSpeed = 0;
  }

  _spinnerPosition += _spinnerSpeed * dt;
  _spinnerPosition = std::fmod(_spinnerPosition, 360.f);

  if (_spinnerPosition < 0) _spinnerPosition += 360.f;

  for (auto& line : _lines) line.Rotate(_spinnerSpeed * dt);
}

void Wheel::Draw(BatchRenderer* renderer, const View& view) {
  Sprite t = _wheelSprite;
  t.Scale(GetScale());
  t.Rotate(GetRotation());
  t.Translate(GetTranslation());

  renderer->DrawSprite(t, view);

  for (auto line : _lines) {
    ConvexShape t = line;
    t.Scale(GetScale());
    t.Rotate(GetRotation());
    t.Translate(GetTranslation());

    renderer->DrawConvexShape(t, view);
  }

  Sprite s = _stopperSprite;
  s.Scale(GetScale());
  s.Rotate(GetRotation());
  s.Translate(GetTranslation());

  renderer->DrawSprite(s, view);
}

void Wheel::SetColor(const Color& color) {
  _wheelSprite.SetColor(color);

  for (auto& line : _lines) line.SetColor(color);
}

void Wheel::SetStopped(const bool_t& _stopped) {
  _direction = sgn(_spinnerSpeed);
  this->_stopped = _stopped;
}

const bool_t& Wheel::GetStopped() const { return _stopped; }
