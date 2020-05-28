#include "KeyIcon.hpp"

KeyIcon::KeyIcon() {}

KeyIcon::KeyIcon(std::string key, Sprite iconSpr, Sprite keySpr, Sprite buttonSpr)
    : _key(key), _iconSprite(iconSpr), _keySprite(keySpr), _buttonSprite(buttonSpr) {
  _buttonSprite.SetTranslation(
      Vec2f(_keySprite.GetTextureSize() - _buttonSprite.GetTextureSize()) / 2);
  _iconSprite.SetTranslation(-Vec2f(_iconSprite.GetTextureSize()) / 2);
}

void KeyIcon::Update(float dt) {
  _iconSprite.UpdateFrame(dt);
  _keySprite.UpdateFrame(dt);
  _buttonSprite.UpdateFrame(dt);
}

void KeyIcon::Draw(BatchRenderer* renderer) {
  for (auto spr : {_keySprite, _buttonSprite, _iconSprite}) {
    Sprite t = spr;
    t.Scale(GetScale());
    t.Rotate(GetRotation());
    t.Translate(GetTranslation());

    renderer->DrawSprite(t);
  }
}
