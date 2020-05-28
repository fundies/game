#include "Banner.hpp"

Banner::Banner() : _box(4) {}

void Banner::SetColor(const Color& _color) { this->_color = _color; }

void Banner::SetIcon(const Sprite& _icon) { this->_icon = _icon; }

void Banner::SetName(const Text& _name) { this->_name = _name; }

void Banner::SetSize(const Vec2f& _size) {
  _box.SetPointPosition(0, Vec2f(0, 0));
  _box.SetPointPosition(1, Vec2f(_size.x, 0));
  _box.SetPointPosition(2, Vec2f(_size.x, _size.y));
  _box.SetPointPosition(3, Vec2f(0, _size.y));

  this->_size = _size;
}

const Color& Banner::GetColor() const { return _color; }

const Sprite& Banner::GetIcon() const { return _icon; }

const Text& Banner::GetName() const { return _name; }

const Vec2f Banner::GetSize() const {
  return Vec2f(_size.x + _icon.GetTextureSize().x, _size.y) * GetScale();
}

void Banner::SetHorizontalAlign(const HorzAlign& _horizontalAlign) { this->_horizontalAlign = _horizontalAlign; }

void Banner::SetVerticalAlign(const VertAlign& _verticalAlign) { this->_verticalAlign = _verticalAlign; }

const HorzAlign& Banner::GetHorizontalAlign() const { return _horizontalAlign; }

const VertAlign& Banner::GetVerticalAlign() const { return _verticalAlign; }

void Banner::SetAlpha(unsigned startAlpha, unsigned endAlpha) {
  _startAlpha = startAlpha;
  _endAlpha = endAlpha;
}

void Banner::Draw(BatchRenderer* renderer) {
  bool alignRight = (_horizontalAlign == HorzAlign::right);
  bool alignTop = (_verticalAlign == VertAlign::top);

  for (unsigned i = 0; i < 4; i++) {
    bool c = (i % 3 == 0);

    if (alignRight) c = !c;

    if (c)
      _box.SetPointColor(i, Color(_color.RedVal, _color.GreenVal, _color.BlueVal, _startAlpha));
    else
      _box.SetPointColor(i, Color(_color.RedVal, _color.GreenVal, _color.BlueVal, _endAlpha));
  }

  _name.SetColor(_color);

  _box.SetScale(GetScale());

  float boxXoff = 0;

  if (!alignRight) boxXoff = _icon.GetTextureSize().x * GetScale().x;

  _box.SetTranslation(Vec2f(boxXoff, 0) + GetTranslation());

  _name.SetScale(GetScale());

  float textXoff;

  if (!alignRight)
    textXoff = _icon.GetTextureSize().x * GetScale().x;
  else
    textXoff = (_size.x - _name.GetTextureSize().x) * GetScale().x;

  float textYoff;

  if (!alignTop)
    textYoff = (_size.y + 12) * GetScale().y;
  else
    textYoff = -_name.GetTextureSize().y * GetScale().y;

  _name.SetTranslation(Vec2f(textXoff, textYoff) + GetTranslation());

  _icon.SetScale(GetScale());

  float iconXoff = 0;

  if (alignRight) iconXoff = _size.x * GetScale().x;

  _icon.SetTranslation(Vec2f(iconXoff, 0) + GetTranslation());

  renderer->DrawConvexShape(_icon);
  renderer->DrawConvexShape(_box);
  renderer->DrawText(_name);
}
