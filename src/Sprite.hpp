#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "ConvexShape.hpp"
#include "TextureQuad.hpp"

#include <string>

class Sprite : public ConvexShape {
 public:
  Sprite();
  Sprite(const TextureQuad& frame);
  void AddFrame(const TextureQuad& frame);
  void RemoveFrame(unsigned index);
  void UpdateFrame(float dt);
  void SetAnimationSpeed(const float& _animationSpeed);
  void SetCurrentFrame(const float& _currentFrame);
  const float& GetAnimationSpeed() const;
  const unsigned GetCurrentFrame() const;
  const unsigned GetFrameCount() const;
  const Vec2f GetTextureSize() const;

 protected:
  std::vector<TextureQuad> _frames;
  float _currentFrame;
  float _animationSpeed;
};

#endif
