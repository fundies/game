#ifndef KEYICON_HPP
#define KEYICON_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Transformable.hpp"
#include "View.hpp"

class KeyIcon : public Transformable {
 public:
  KeyIcon();
  KeyIcon(string_t key, Sprite iconSpr, Sprite keySpr, Sprite buttonSpr);
  void Update(float_type dt);
  void Draw(BatchRenderer* renderer, const View& view);
  const string_t& GetName() const;

 protected:
  string_t _key;
  Sprite _iconSprite;
  Sprite _keySprite;
  Sprite _buttonSprite;
};

#endif
