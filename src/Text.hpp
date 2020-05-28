#ifndef TEXT_HPP
#define TEXT_HPP

#include "ResourceManager.hpp"
#include "Transformable.hpp"

#include <string>

class Text : public Transformable {
 public:
  Text();
  Text(std::string font, std::string string);

  void SetScale(const Vec2f& scale);
  void SetColor(const Color& _color);
  void SetFont(const std::string& _font);
  void SetString(const std::string& _string);
  void SetShadowColor(const Color& _shadowColor);
  void SetShadowPosition(const Vec2f& _shadowPosition);
  const Color& GetShadowColor() const;
  const Vec2f& GetShadowPosition() const;

  const Color& GetColor() const;
  const std::string& GetFont() const;
  const std::string& GetString() const;

  const Vec2f& GetTextureSize() const;
  const std::vector<Sprite>& GetLetters() const;

 protected:
  std::string _font;
  std::string _string;
  Color _color;
  std::vector<Sprite> _letters;
  Vec2f _textureSize;
  Vec2f _shadowPosition;
  Color _shadowColor;
};

#endif
