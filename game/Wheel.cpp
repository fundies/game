#include "Wheel.hpp"

Wheel::Wheel() : _spinnerPosition(0), _spinnerSpeed(0), _stopped(false) {}

void Wheel::SetInnerRadius(const unsigned& _innerRadius) { this->_innerRadius = _innerRadius; }

void Wheel::SetNumberSlices(const unsigned& _numberSlices) {
  this->_numberSlices = _numberSlices;

  _lines.clear();

  for (unsigned c = 0; c < _numberSlices; c++) {
    int lineWidth = 3;

    float outerRadius = _wheelSprite.GetTextureSize().x / 2;

    float x1 = outerRadius;
    float y1 = outerRadius;

    float a = c * (360.f / _numberSlices);
    float y2 = _innerRadius * std::cos((a * M_PI) / 180);
    y2 += outerRadius;

    float x2 = _innerRadius * std::sin((a * M_PI) / 180);
    x2 += outerRadius;

    float dir = std::fmod(std::atan2(y1 - y2, x2 - x1) + 2 * M_PI, 2 * M_PI);
    float cv = std::cos(dir - M_PI / 2.0);
    float sv = -std::sin(dir - M_PI / 2.0);
    float dw = lineWidth / 2.0;

    ConvexShape line(4);
    line.SetPointPosition(0, Vec2f(x1 + dw * cv, y1 + dw * sv));
    line.SetPointPosition(1, Vec2f(x1 - dw * cv, y1 - dw * sv));
    line.SetPointPosition(2, Vec2f(x2 + dw * cv, y2 + dw * sv));
    line.SetPointPosition(3, Vec2f(x2 - dw * cv, y2 - dw * sv));

    line.SetPivot(Vec2f(outerRadius, outerRadius));

    _lines.push_back(line);
  }
}

void Wheel::SetSpinnerPosition(const float& _spinnerPosition) { this->_spinnerPosition = _spinnerPosition; }

void Wheel::SetSpinnerSpeed(const float& _spinnerSpeed) { this->_spinnerSpeed = _spinnerSpeed; }

void Wheel::SetStopSpeed(const float& _stopSpeed) { this->_stopSpeed = _stopSpeed; }

void Wheel::SetStopperSprite(const Sprite& _stopperSprite) {
  this->_stopperSprite = _stopperSprite;
  this->_stopperSprite.SetTranslation(Vec2f(
      (_wheelSprite.GetTextureSize().x - _stopperSprite.GetTextureSize().x) / 2, -_stopperSprite.GetTextureSize().x));
}

void Wheel::SetWheelSprite(const Sprite& _wheelSprite) { this->_wheelSprite = _wheelSprite; }

const unsigned& Wheel::GetInnerRadius() const { return _innerRadius; }

const unsigned& Wheel::GetNumberSlices() const { return _numberSlices; }

const unsigned Wheel::GetSpinnerPosition() const {
  float w = 360.f / _numberSlices;
  return (_numberSlices) - (_spinnerPosition / w);
}

const float& Wheel::GetSpinnerSpeed() const { return _spinnerSpeed; }

const float& Wheel::GetStopSpeed() const { return _stopSpeed; }

const Sprite& Wheel::GetStopperSprite() const { return _stopperSprite; }

const Sprite& Wheel::GetWheelSprite() const { return _wheelSprite; }

void Wheel::Update(float dt) {
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

void Wheel::Draw(BatchRenderer* renderer) {
  Sprite t = _wheelSprite;
  t.Scale(GetScale());
  t.Rotate(GetRotation());
  t.Translate(GetTranslation());

  renderer->DrawSprite(t);

  for (auto line : _lines) {
    ConvexShape t = line;
    t.Scale(GetScale());
    t.Rotate(GetRotation());
    t.Translate(GetTranslation());

    renderer->DrawConvexShape(t);
  }

  Sprite s = _stopperSprite;
  s.Scale(GetScale());
  s.Rotate(GetRotation());
  s.Translate(GetTranslation());

  renderer->DrawSprite(s);
}

void Wheel::SetColor(const Color& color) {
  _wheelSprite.SetColor(color);

  for (auto& line : _lines) line.SetColor(color);
}

void Wheel::SetStopped(const bool& _stopped) {
  _direction = sgn(_spinnerSpeed);
  this->_stopped = _stopped;
}

const bool& Wheel::GetStopped() const { return _stopped; }
