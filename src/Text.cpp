#include "Text.hpp"

Text::Text() {}

Text::Text(std::string font, std::string string) : _font(font) { SetString(string); }

void Text::SetColor(const Color& _color) {
  this->_color = _color;

  for (auto& c : _letters) {
    c.SetColor(_color);
  }
}
void Text::SetFont(const std::string& _font) { this->_font = _font; }

void Text::SetString(const std::string& _string) {
  this->_string = _string;

  _letters.clear();

  Vec2f pos(0, 0);

  for (auto& c : _string) {
    int l = static_cast<int>(c);
    Sprite letter = ResourceManager::GetSprite(_font + "_" + std::to_string(l));
    letter.SetTranslation(pos);
    _letters.push_back(letter);

    pos += Vec2f(letter.GetTextureSize().x, 0);
  }

  _textureSize = Vec2f(pos.x, _letters[0].GetTextureSize().y);
}

void Text::SetScale(const Vec2f& scale) {
  Vec2f pos(0, 0);

  for (auto& c : _letters) {
    c.SetTranslation(pos);
    pos += Vec2f(c.GetTextureSize().x * scale.x, 0);
  }

  Transformable::SetScale(scale);
}

const Color& Text::GetColor() const { return _color; }

const std::string& Text::GetFont() const { return _font; }

const std::string& Text::GetString() const { return _string; }

const Vec2f& Text::GetTextureSize() const { return _textureSize; }

const std::vector<Sprite>& Text::GetLetters() const { return _letters; }

void Text::SetShadowColor(const Color& _shadowColor) { this->_shadowColor = _shadowColor; }

void Text::SetShadowPosition(const Vec2f& _shadowPosition) {
  this->_shadowPosition = _shadowPosition;
}

const Color& Text::GetShadowColor() const { return _shadowColor; }

const Vec2f& Text::GetShadowPosition() const { return _shadowPosition; }
