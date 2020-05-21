#ifndef BANNER_HPP
#define BANNER_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Transformable.hpp"
#include "View.hpp"

enum class HorzAlign : uint_t { left, right };

enum class VertAlign : uint_t { top, bottom };

class Banner : public Transformable {
 public:
  Banner();
  void SetColor(const Color& _color);
  void SetIcon(const Sprite& _icon);
  void SetName(const Text& _name);
  void SetSize(const ENGINE::Vector2<float_type>& _size);
  const Color& GetColor() const;
  const Sprite& GetIcon() const;
  const Text& GetName() const;
  const ENGINE::Vector2<float_type> GetSize() const;
  void Draw(BatchRenderer* renderer, View& view);
  void SetHorizontalAlign(const HorzAlign& _horizontalAlign);
  void SetVerticalAlign(const VertAlign& _verticalAlign);
  const HorzAlign& GetHorizontalAlign() const;
  const VertAlign& GetVerticalAlign() const;
  void SetAlpha(uint_t startAlpha, uint_t endAlpha);

 protected:
  ConvexShape _box;
  Sprite _icon;
  Color _color;
  ENGINE::Vector2<float_type> _size;
  Text _name;
  HorzAlign _horizontalAlign;
  VertAlign _verticalAlign;
  uint_t _startAlpha;
  uint_t _endAlpha;
};

#endif
