#ifndef BANNER_HPP
#define BANNER_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Transformable.hpp"

enum class HorzAlign : unsigned { left, right };

enum class VertAlign : unsigned { top, bottom };

class Banner : public Transformable {
 public:
  Banner();
  void SetColor(const Color& _color);
  void SetIcon(const Sprite& _icon);
  void SetName(const Text& _name);
  void SetSize(const Vec2f& _size);
  const Color& GetColor() const;
  const Sprite& GetIcon() const;
  const Text& GetName() const;
  const Vec2f GetSize() const;
  void Draw(BatchRenderer* renderer);
  void SetHorizontalAlign(const HorzAlign& _horizontalAlign);
  void SetVerticalAlign(const VertAlign& _verticalAlign);
  const HorzAlign& GetHorizontalAlign() const;
  const VertAlign& GetVerticalAlign() const;
  void SetAlpha(unsigned startAlpha, unsigned endAlpha);

 protected:
  ConvexShape _box;
  Sprite _icon;
  Color _color;
  Vec2f _size;
  Text _name;
  HorzAlign _horizontalAlign;
  VertAlign _verticalAlign;
  unsigned _startAlpha;
  unsigned _endAlpha;
};

#endif
