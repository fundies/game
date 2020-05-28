#ifndef KEYICON_HPP
#define KEYICON_HPP

#include "BatchRenderer.hpp"
#include "Sprite.hpp"
#include "Transformable.hpp"

class KeyIcon : public Transformable {
 public:
  KeyIcon();
  KeyIcon(std::string key, Sprite iconSpr, Sprite keySpr, Sprite buttonSpr);
  void Update(float dt);
  void Draw(BatchRenderer* renderer);
  const std::string& GetName() const;

 protected:
  std::string _key;
  Sprite _iconSprite;
  Sprite _keySprite;
  Sprite _buttonSprite;
};

#endif
