#include "Text.hpp"

Text::Text() {}

Text::Text(string_t font, string_t string) : _font(font) { SetString(string); }

void Text::SetColor(const Color& _color) {
  this->_color = _color;

  for (auto& c : _letters) {
    c.SetColor(_color);
  }
}
void Text::SetFont(const string_t& _font) { this->_font = _font; }

void Text::SetString(const string_t& _string) {
  this->_string = _string;

  _letters.clear();

  ENGINE::Vector2<float_type> pos(0, 0);

  for (auto& c : _string) {
    int l = static_cast<int>(c);
    Sprite letter = ResourceManager::GetSprite(_font + "_" + std::to_string(l));
    letter.SetTranslation(pos);
    _letters.push_back(letter);

    pos += ENGINE::Vector2<float_type>(letter.GetTextureSize().x, 0);
  }

  _textureSize = ENGINE::Vector2<float_type>(pos.x, _letters[0].GetTextureSize().y);
}

void Text::SetScale(const ENGINE::Vector2<float_type>& scale) {
  ENGINE::Vector2<float_type> pos(0, 0);

  for (auto& c : _letters) {
    c.SetTranslation(pos);
    pos += ENGINE::Vector2<float_type>(c.GetTextureSize().x * scale.x, 0);
  }

  Transformable::SetScale(scale);
}

const Color& Text::GetColor() const { return _color; }

const string_t& Text::GetFont() const { return _font; }

const string_t& Text::GetString() const { return _string; }

const ENGINE::Vector2<float_type>& Text::GetTextureSize() const { return _textureSize; }

const vector_t<Sprite>& Text::GetLetters() const { return _letters; }

void Text::SetShadowColor(const Color& _shadowColor) { this->_shadowColor = _shadowColor; }

void Text::SetShadowPosition(const ENGINE::Vector2<float_type>& _shadowPosition) {
  this->_shadowPosition = _shadowPosition;
}

const Color& Text::GetShadowColor() const { return _shadowColor; }

const ENGINE::Vector2<float_type>& Text::GetShadowPosition() const { return _shadowPosition; }
