#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Color.hpp"
#include "Vector2.hpp"

class Vertex {
 public:
  Vertex(const Vec2f& _position = Vec2f(0.f, 0.f),
         const Vec2f& _texturePos = Vec2f(0.f, 0.f),
         const Color& _color = Color(255, 255, 255, 255));

  void SetColor(const Color& _color);
  void SetPosition(const Vec2f& _position);
  void SetTexturePos(const Vec2f& _texturePos);
  const Color& GetColor() const;
  const Vec2f& GetPosition() const;
  const Vec2f& GetTexturePosition() const;
  Vec2f& GetTexturePositionM();

 protected:
  Vec2f _position;
  Vec2f _texturePos;
  Color _color;
};

#endif
