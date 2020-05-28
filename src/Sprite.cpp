#include "Sprite.hpp"
#include "Logger.hpp"

#include <cmath>

Sprite::Sprite() : ConvexShape(4), _currentFrame(0), _animationSpeed(0) {}

Sprite::Sprite(const TextureQuad& frame) : ConvexShape(4), _currentFrame(0), _animationSpeed(0) { AddFrame(frame); }

void Sprite::AddFrame(const TextureQuad& frame) {
  if (_frames.empty()) {
    Vec2f size = frame.GetSize();

    SetPointPosition(0, Vec2f(0, 0));
    SetPointPosition(1, Vec2f(size.x, 0));
    SetPointPosition(2, Vec2f(size.x, size.y));
    SetPointPosition(3, Vec2f(0, size.y));

    _frames.push_back(frame);

    SetCurrentFrame(0);

    CalcCenter();

    return;
  } else
    _frames.push_back(frame);
}

void Sprite::RemoveFrame(unsigned index) { _frames.erase(_frames.begin() + index); }

void Sprite::UpdateFrame(float dt) {
  if (!_frames.empty()) {
    _currentFrame += _animationSpeed * dt;
    _currentFrame = std::fmod(_currentFrame, _frames.size());

    if (_currentFrame < 0) _currentFrame += _frames.size();

    SetCurrentFrame(_currentFrame);
  }
}

void Sprite::SetAnimationSpeed(const float& _animationSpeed) { this->_animationSpeed = _animationSpeed; }

void Sprite::SetCurrentFrame(const float& _currentFrame) {
  this->_currentFrame = _currentFrame;

  const TextureQuad& t = _frames[static_cast<unsigned>(_currentFrame)];
  const Vec2f& tPos = t.GetPosition();
  const Vec2f& tSize = t.GetSize();

  SetPointTexturePosition(0, Vec2f(tPos.x, tPos.y));
  SetPointTexturePosition(1, Vec2f(tPos.x + tSize.x, tPos.y));
  SetPointTexturePosition(2, Vec2f(tPos.x + tSize.x, tPos.y + tSize.y));
  SetPointTexturePosition(3, Vec2f(tPos.x, tPos.y + tSize.y));
}

const float& Sprite::GetAnimationSpeed() const { return _animationSpeed; }

const unsigned Sprite::GetCurrentFrame() const { return static_cast<unsigned>(_currentFrame); }

const unsigned Sprite::GetFrameCount() const { return _frames.size(); }

const Vec2f Sprite::GetTextureSize() const {
  if (!_frames.empty())
    return _frames[static_cast<unsigned>(_currentFrame)].GetSize();
  else {
    PrintMessage("ERROR::SPRITE: Trying to get size of empty sprite returning (0,0)");
    return Vec2f(0, 0);
  }
}
