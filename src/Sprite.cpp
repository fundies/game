#include "Sprite.hpp"
#include "Logger.hpp"

#include <cmath>

Sprite::Sprite() : ConvexShape(4), _currentFrame(0), _animationSpeed(0) {}

Sprite::Sprite(const TextureQuad& frame) : ConvexShape(4), _currentFrame(0), _animationSpeed(0) { AddFrame(frame); }

void Sprite::AddFrame(const TextureQuad& frame) {
  if (_frames.empty()) {
    ENGINE::Vector2<float_type> size = frame.GetSize();

    SetPointPosition(0, ENGINE::Vector2<float_type>(0, 0));
    SetPointPosition(1, ENGINE::Vector2<float_type>(size.x, 0));
    SetPointPosition(2, ENGINE::Vector2<float_type>(size.x, size.y));
    SetPointPosition(3, ENGINE::Vector2<float_type>(0, size.y));

    _frames.push_back(frame);

    SetCurrentFrame(0);

    CalcCenter();

    return;
  } else
    _frames.push_back(frame);
}

void Sprite::RemoveFrame(uint_t index) { _frames.erase(_frames.begin() + index); }

void Sprite::UpdateFrame(float_type dt) {
  if (!_frames.empty()) {
    _currentFrame += _animationSpeed * dt;
    _currentFrame = std::fmod(_currentFrame, _frames.size());

    if (_currentFrame < 0) _currentFrame += _frames.size();

    SetCurrentFrame(_currentFrame);
  }
}

void Sprite::SetAnimationSpeed(const float_type& _animationSpeed) { this->_animationSpeed = _animationSpeed; }

void Sprite::SetCurrentFrame(const float_type& _currentFrame) {
  this->_currentFrame = _currentFrame;

  const TextureQuad& t = _frames[static_cast<uint_t>(_currentFrame)];
  const ENGINE::Vector2<float_type>& tPos = t.GetPosition();
  const ENGINE::Vector2<float_type>& tSize = t.GetSize();

  SetPointTexturePosition(0, ENGINE::Vector2<float_type>(tPos.x, tPos.y));
  SetPointTexturePosition(1, ENGINE::Vector2<float_type>(tPos.x + tSize.x, tPos.y));
  SetPointTexturePosition(2, ENGINE::Vector2<float_type>(tPos.x + tSize.x, tPos.y + tSize.y));
  SetPointTexturePosition(3, ENGINE::Vector2<float_type>(tPos.x, tPos.y + tSize.y));
}

const float_type& Sprite::GetAnimationSpeed() const { return _animationSpeed; }

const uint_t Sprite::GetCurrentFrame() const { return static_cast<uint_t>(_currentFrame); }

const uint_t Sprite::GetFrameCount() const { return _frames.size(); }

const ENGINE::Vector2<float_type> Sprite::GetTextureSize() const {
  if (!_frames.empty())
    return _frames[static_cast<uint_t>(_currentFrame)].GetSize();
  else {
    PrintMessage("ERROR::SPRITE: Trying to get size of empty sprite returning (0,0)");
    return ENGINE::Vector2<float_type>(0, 0);
  }
}
