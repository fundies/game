#ifndef TEXT_HPP
#define TEXT_HPP

#include "ResourceManager.hpp"
#include "Transformable.hpp"

#include <string>

class Text : public Transformable {
 public:
  Text();
  Text(string_t font, string_t string);

  void SetScale(const ENGINE::Vector2<float_type>& scale);
  void SetColor(const Color& _color);
  void SetFont(const string_t& _font);
  void SetString(const string_t& _string);
  void SetShadowColor(const Color& _shadowColor);
  void SetShadowPosition(const ENGINE::Vector2<float_type>& _shadowPosition);
  const Color& GetShadowColor() const;
  const ENGINE::Vector2<float_type>& GetShadowPosition() const;

  const Color& GetColor() const;
  const string_t& GetFont() const;
  const string_t& GetString() const;

  const ENGINE::Vector2<float_type>& GetTextureSize() const;
  const vector_t<Sprite>& GetLetters() const;

 protected:
  string_t _font;
  string_t _string;
  Color _color;
  vector_t<Sprite> _letters;
  ENGINE::Vector2<float_type> _textureSize;
  ENGINE::Vector2<float_type> _shadowPosition;
  Color _shadowColor;
};

#endif
