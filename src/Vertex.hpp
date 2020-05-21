#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Color.hpp"
#include "Vector2.hpp"

class Vertex {
 public:
  Vertex(const ENGINE::Vector2<float_type>& _position = ENGINE::Vector2<float_type>(0.f, 0.f),
         const ENGINE::Vector2<float_type>& _texturePos = ENGINE::Vector2<float_type>(0.f, 0.f),
         const Color& _color = Color(255, 255, 255, 255));

  void SetColor(const Color& _color);
  void SetPosition(const ENGINE::Vector2<float_type>& _position);
  void SetTexturePos(const ENGINE::Vector2<float_type>& _texturePos);
  const Color& GetColor() const;
  const ENGINE::Vector2<float_type>& GetPosition() const;
  const ENGINE::Vector2<float_type>& GetTexturePosition() const;
  ENGINE::Vector2<float_type>& GetTexturePositionM();

 protected:
  ENGINE::Vector2<float_type> _position;
  ENGINE::Vector2<float_type> _texturePos;
  Color _color;
};

#endif
