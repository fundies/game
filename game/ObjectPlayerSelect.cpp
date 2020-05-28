#include "ObjectPlayerSelect.hpp"
#include "Input.hpp"
#include "Text.hpp"

ObjectPlayerSelect::ObjectPlayerSelect()
    : Object(),
      currSelectColumn(0),
      selectColumns(2),
      currSelectRow(0),
      selectRows(4),
      changedSelection(false),
      currentPlayer(0),
      playerCount(4),
      banner(5),
      bannerStartPos(450, 450),
      bannerPos(bannerStartPos),
      bannerEndPos(-100, -100),
      bannerOffset(40, 200),
      bannerSpeed(20),
      charIconOffset(175, 75),
      _nameIconSpr(ResourceManager::GetSprite("selectName")),
      _nameIconOffset(220, 350) {
  banner.SetPointPosition(0, Vec2f(0, 0));
  banner.SetPointPosition(1, Vec2f(200, 0));
  banner.SetPointPosition(2, Vec2f(200, 1000));
  banner.SetPointPosition(3, Vec2f(100, 1100));
  banner.SetPointPosition(4, Vec2f(0, 1000));
  banner.CalcCenter();

  banner.SetPivot(Vec2f(banner.GetWidth() / 2, banner.GetHeight() / 2));
}

Instance ObjectPlayerSelect::Create(Transformation<float> t) {
  Instance inst(new ObjectPlayerSelect());
  return inst;
}

void ObjectPlayerSelect::PostCollision(float dt) {
  if (Input::ButtonPressed(GameControl::Right) && currSelectColumn < selectColumns - 1) {
    changedSelection = true;
    currSelectColumn++;
  }

  if (Input::ButtonPressed(GameControl::Left) && currSelectColumn > 0) {
    changedSelection = true;
    currSelectColumn--;
  }

  if (Input::ButtonPressed(GameControl::Down) && currSelectRow < selectRows - 1) {
    changedSelection = true;
    currSelectRow++;
  }

  if (Input::ButtonPressed(GameControl::Up) && currSelectRow > 0) {
    changedSelection = true;
    currSelectRow--;
  }

  if (Input::ButtonPressed(GameControl::A)) {
    if (currentPlayer < playerCount - 1) {
      currentPlayer++;
      currSelectRow = 0;
      currSelectColumn = 0;
      changedSelection = true;
    } else
      ResourceManager::SetCurrentLevel("sutton");
  }

  if (changedSelection) {
    bannerPos = bannerStartPos;
    changedSelection = false;
    _nameIconSpr.SetCurrentFrame(0);
  }

  if (bannerPos.x > bannerEndPos.x || bannerPos.y > bannerEndPos.y) {
    bannerPos.x -= bannerSpeed;
    bannerPos.y -= bannerSpeed;
  }

  if (_nameIconSpr.GetCurrentFrame() < _nameIconSpr.GetFrameCount() - 1) _nameIconSpr.UpdateFrame(dt);
}

void ObjectPlayerSelect::DrawGUI(BatchRenderer* _renderer) {
  _renderer->DrawSprite(ResourceManager::GetSprite("menubkgd"));

  //unsigned currentSelection = selectRow*2+(selectColumn);

  Sprite ico = ResourceManager::GetSprite("charselectphoto");

  Vec2f offset((RES_W - (ico.GetTextureSize().x * selectColumns)) / 2,
                                (RES_H - (ico.GetTextureSize().y * selectRows)) / 2);

  Vec2f selectedPlayerPos;

  for (unsigned i = 0; i < selectColumns; i++) {
    for (unsigned j = 0; j < selectRows; j++) {
      ico.SetScale(Vec2f(1, 1));
      ico.SetTranslation(Vec2f(i * ico.GetTextureSize().x, j * ico.GetTextureSize().y));
      ico.Translate(offset);

      if (i == currSelectColumn && j == currSelectRow) {
        selectedPlayerPos = ico.GetTranslation();
        ico.Translate(((ico.GetTextureSize() * ico.GetScale()) - ico.GetTextureSize()) / 2);
        ico.SetScale(Vec2f(1.1, 1.1));
      }

      else
        _renderer->DrawSprite(ico);
    }
  }

  ico.SetScale(Vec2f(1.1, 1.1));
  Vec2f soffset = ((ico.GetTextureSize() * ico.GetScale()) - ico.GetTextureSize()) / 2;
  ico.SetTranslation(Vec2f(selectedPlayerPos.x - soffset.x, selectedPlayerPos.y - soffset.y));
  _renderer->DrawSprite(ico);

  for (unsigned player = 0; player <= currentPlayer; ++player) {
    Vec2f tempPos;
    Sprite tempName = _nameIconSpr;

    if (player < currentPlayer) {
      tempPos = bannerEndPos;
      tempName.SetCurrentFrame(_nameIconSpr.GetFrameCount() - 1);
    } else
      tempPos = bannerPos;

    Vec2f flip(1, 1);
    Vec2f scale(-1, -1);
    Vec2f offset(0, 0);
    int rot = 45;

    Sprite characterIcon = ResourceManager::GetSprite("trevor_player_select");
    Text name("LuckiestGuy_52", "Trevor");

    Vec2f iconScale(1, 1);
    Vec2f iconOffset(0, 0);

    Vec2f nameScale(1, 1);
    Vec2f nameOffset(0, 0);
    Vec2f nameTextOffset(0, 0);

    nameOffset.y = _nameIconOffset.y;

    if (player == 0 || player == 1) {
      offset.y = bannerOffset.y;
      flip.y = -1;
      iconOffset.y = charIconOffset.y;
    }

    if (player == 0 || player == 2) {
      offset.x = bannerOffset.x;
      iconOffset.x = charIconOffset.x;
      nameOffset.x = _nameIconOffset.x + _nameIconSpr.GetTextureSize().x;
      nameScale.x = -1;
      nameTextOffset.x = nameOffset.x - _nameIconSpr.GetTextureSize().x + 150;
    }

    if (player == 1 || player == 2) rot = -45;

    if (player == 1 || player == 3) {
      offset.x = -RES_W + banner.GetWidth() - bannerOffset.x;
      flip.x = -1;
      iconOffset.x = RES_W - charIconOffset.x;
      iconScale.x = -1;
      nameOffset.x = RES_W - _nameIconOffset.x - _nameIconSpr.GetTextureSize().x;
      nameTextOffset.x = nameOffset.x + name.GetTextureSize().x - 150;
    }

    if (player == 2 || player == 3) {
      scale.y = 1;
      offset.y = -bannerOffset.y;
      iconOffset.y = RES_H - charIconOffset.y - characterIcon.GetTextureSize().y;
      nameOffset.y = RES_H - _nameIconOffset.y - _nameIconSpr.GetTextureSize().y;
    }

    nameTextOffset.y = nameOffset.y + 50;

    if (player == 3) scale.x = 1;

    Color color;

    switch (player) {
      case 0: {
        color = Color(255, 0, 0, 255);
        break;
      }

      case 1: {
        color = Color(0, 255, 0, 255);
        break;
      }

      case 2: {
        color = Color(0, 0, 255, 255);
        break;
      }

      case 3: {
        color = Color(255, 255, 0, 255);
        break;
      }
    }

    banner.SetTranslation(-offset - (tempPos * flip));
    banner.SetScale(scale);
    banner.SetRotation(rot);
    banner.SetColor(color);
    //_renderer->DrawConvexShape(banner);

    tempName.SetTranslation(nameOffset);
    tempName.SetColor(color);
    tempName.SetScale(nameScale);
    _renderer->DrawSprite(tempName);

    name.SetScale(Vec2f(1.5, 1.5));
    name.Translate(nameTextOffset);
    _renderer->DrawText(name);

    characterIcon.Translate(iconOffset);
    characterIcon.SetScale(iconScale);
    _renderer->DrawSprite(characterIcon);
  }

  /*if (currentPlayer >= 0)
	{
		Vec2f bannerPos = p;

		if (currentPlayer > 0)
			bannerPos = Vec2f(-100, -100);

		banner.SetTranslation(Vec2f(-40 - bannerPos.x, -200 + bannerPos.y));

		banner.SetScale(Vec2f(1, -1));
		banner.SetRotation(45);
		_renderer->DrawConvexShape(banner);

		Sprite icon = ResourceManager::GetSprite("trevor_player_select");
		icon.Translate(Vec2f(175, 75));
		_renderer->DrawSprite(icon);
	}

	if (currentPlayer >= 1)
	{
		Vec2f bannerPos = p;

		if (currentPlayer > 1)
			bannerPos = Vec2f(-100, -100);

		banner.SetTranslation(ENGINE::Vector2(-40.f - bannerPos.x, 200.f - bannerPos.y));
		banner.SetScale(Vec2f(1, 1));
		banner.SetRotation(-45);
		_renderer->DrawConvexShape(banner);

		Sprite icon = ResourceManager::GetSprite("trevor_player_select");
		icon.Translate(Vec2f(175, 1080-75-icon.GetTextureSize().y));
		_renderer->DrawSprite(icon);
	}

	if (currentPlayer >= 2)
	{
		Vec2f bannerPos = p;

		if (currentPlayer > 2)
			bannerPos = Vec2f(-100, -100);

		banner.SetTranslation(ENGINE::Vector2(1920 - (200) + 40 + bannerPos.x, -200.f + bannerPos.y));
		banner.SetScale(Vec2f(1, -1));
		banner.SetRotation(-45);
		_renderer->DrawConvexShape(banner);

		Sprite icon = ResourceManager::GetSprite("trevor_player_select");
		icon.Translate(Vec2f(1920 - 175, 75));
		icon.SetScale(Vec2f(-1, 1));
		_renderer->DrawSprite(icon);
	}

	if (currentPlayer >= 3)
	{
		Vec2f bannerPos = p;

		if (currentPlayer > 3)
			bannerPos = Vec2f(-100, -100);

		banner.SetTranslation(ENGINE::Vector2(1920 - (200) + 40 + bannerPos.x, 200.f - bannerPos.y));
		banner.SetScale(Vec2f(1, 1));
		banner.SetRotation(45);
		_renderer->DrawConvexShape(banner);

		Sprite icon = ResourceManager::GetSprite("trevor_player_select");
		icon.Translate(Vec2f(1920 - 175, 1080-75-icon.GetTextureSize().y));
		icon.SetScale(Vec2f(-1, 1));
		_renderer->DrawSprite(icon);
	}*/
}
