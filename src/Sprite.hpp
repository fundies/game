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
  void RemoveFrame(uint_t index);
  void UpdateFrame(float_type dt);
  void SetAnimationSpeed(const float_type& _animationSpeed);
  void SetCurrentFrame(const float_type& _currentFrame);
  const float_type& GetAnimationSpeed() const;
  const uint_t GetCurrentFrame() const;
  const uint_t GetFrameCount() const;
  const ENGINE::Vector2<float_type> GetTextureSize() const;

 protected:
  vector_t<TextureQuad> _frames;
  float_type _currentFrame;
  float_type _animationSpeed;
};

#endif
