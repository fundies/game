#include "ObjectHUD.hpp"
#include "ResourceManager.hpp"

Instance ObjectHUD::Create(Transformation<float_type> t) {
  Instance inst(new ObjectHUD());
  return inst;
}

ObjectHUD::ObjectHUD()
    : Object(),
      _currentPlayer(0),
      _playerTurn(0),
      _numPlayers(2),
      _donePlayerMoves(false),
      _viewingMap(false),
      _startAlpha(255),
      _endAlpha(55),
      _hudSize(450, 150),
      _hudSpacing(20),
      _viewMapSpeed(16),
      _arrowSprite(ResourceManager::GetSprite("maparrow")) {
  _players.push_back(PlayerInfo("trevor", Color(232, 13, 13, 255), ResourceManager::GetSprite("potrait_trevor"),
                                ResourceManager::GetSprite("map trevor"),
                                ResourceManager::GetLevel("sutton").GetBoardStartSpace()));

  _players.push_back(PlayerInfo("greg", Color(28, 168, 57, 255), ResourceManager::GetSprite("potrait_greg"),
                                ResourceManager::GetSprite("map greg"),
                                ResourceManager::GetLevel("sutton").GetBoardStartSpace()));

  _players.push_back(PlayerInfo("neesh", Color(61, 135, 182, 255), ResourceManager::GetSprite("potrait_neesh"),
                                ResourceManager::GetSprite("map neesh"),
                                ResourceManager::GetLevel("sutton").GetBoardStartSpace()));

  _players.push_back(PlayerInfo("lizz", Color(74, 39, 144, 255), ResourceManager::GetSprite("potrait_lizz"),
                                ResourceManager::GetSprite("map lizz"),
                                ResourceManager::GetLevel("sutton").GetBoardStartSpace()));

  for (uint_t player = 0; player < _numPlayers; player++) {
    _players[player].SetNumberOfMoves(8);

    Text name("LuckiestGuy_52", _players[player].GetName());
    name.SetShadowPosition(ENGINE::Vector2<float_type>(4, 4));

    _banner[player].SetName(name);
    _banner[player].SetIcon(_players[player].GetHUDIcon());
    _banner[player].SetSize(ENGINE::Vector2<float_type>(_hudSize.x, _hudSize.y));
    _banner[player].SetColor(_players[player].GetColor());
    _banner[player].SetAlpha(_startAlpha, _endAlpha);
  }

  _keys["item"] = KeyIcon("s", ResourceManager::GetSprite("box"), ResourceManager::GetSprite("keyicon"),
                          ResourceManager::GetSprite("LuckiestGuy_52_83"));

  _keys["map"] = KeyIcon("a", ResourceManager::GetSprite("mapIcon"), ResourceManager::GetSprite("keyicon"),
                         ResourceManager::GetSprite("LuckiestGuy_52_65"));

  _keys["confirm"] = KeyIcon("x", ResourceManager::GetSprite("confirm"), ResourceManager::GetSprite("keyicon"),
                             ResourceManager::GetSprite("LuckiestGuy_52_88"));

  _keys["cancel"] = KeyIcon("z", ResourceManager::GetSprite("cancel"), ResourceManager::GetSprite("keyicon"),
                            ResourceManager::GetSprite("LuckiestGuy_52_90"));

  _keys["stop"] = KeyIcon("x", ResourceManager::GetSprite("stop"), ResourceManager::GetSprite("keyicon"),
                          ResourceManager::GetSprite("LuckiestGuy_52_88"));

  _wheel.SetWheelSprite(ResourceManager::GetSprite("gamewheel"));
  _wheel.SetStopperSprite(ResourceManager::GetSprite("gamewheelstopper"));
  _wheel.SetTranslation(ENGINE::Vector2<float_type>((RES_W - _wheel.GetWheelSprite().GetTextureSize().x) / 2, 75));
  _wheel.SetInnerRadius(400);
  _wheel.SetNumberSlices(6);
  _wheel.SetColor(_players[_currentPlayer].GetColor());
  _wheel.SetSpinnerSpeed(0.5);
  _wheel.SetStopSpeed(0.0025);

  View& view = ResourceManager::GetLevel("sutton").GetView();
  view.SetTranslation(ENGINE::Vector2<float_type>(0, RES_H));
}

void ObjectHUD::Draw(BatchRenderer* _renderer, View& view) {
  map_t<ENGINE::Vector2<int_t>, vector_t<uint_t>> uniqueBoardSpace;

  for (uint_t player = 0; player < _numPlayers; player++)
    uniqueBoardSpace[_players[player].GetBoardPosition()].push_back(player);

  for (auto boardSpace : uniqueBoardSpace) {
    uint_t index = 0;
    uint_t playersOnSpace = boardSpace.second.size();

    for (auto player : boardSpace.second) {
      float_type xoffset = 0;
      float_type yoffset = 0;

      if (playersOnSpace >= 2) {
        xoffset = ResourceManager::GetSprite("map trevor").GetTextureSize().x / 2;

        if (playersOnSpace >= 3) yoffset = ResourceManager::GetSprite("map trevor").GetTextureSize().y / 2;
      }

      Sprite& spr = _players[player].GetMapIcon();
      spr.SetTranslation(_players[player].GetBoardPosition() +
                         ENGINE::Vector2<float_type>(spr.GetTextureSize().x / 2, 0));

      if (index == 2 && playersOnSpace == 3)
        ;
      else if (index % 2 == 0)
        spr.Translate(ENGINE::Vector2<float_type>(-xoffset, 0));
      else
        spr.Translate(ENGINE::Vector2<float_type>(xoffset, 0));

      if (index < 2)
        spr.Translate(ENGINE::Vector2<float_type>(0, -yoffset));
      else
        spr.Translate(ENGINE::Vector2<float_type>(0, yoffset));

      _renderer->DrawSprite(spr, view);

      index++;
    }
  }

  if (!_donePlayerMoves) {
    Text movesText;
    movesText.SetFont("LuckiestGuy_120");
    movesText.SetString(std::to_string(_players[_currentPlayer].GetNumberOfMoves()));
    movesText.SetColor(_players[_currentPlayer].GetColor());
    movesText.SetShadowPosition(ENGINE::Vector2<float_type>(4, 4));
    movesText.SetTranslation(ENGINE::Vector2<float_type>(
        _players[_currentPlayer].GetMapIcon().GetTranslation().x +
            ((_players[_currentPlayer].GetMapIcon().GetTextureSize().x - movesText.GetTextureSize().x) / 2),
        _players[_currentPlayer].GetMapIcon().GetTranslation().y -
            _players[_currentPlayer].GetMapIcon().GetTextureSize().y));

    _renderer->DrawText(movesText, view);
  }
}

void ObjectHUD::DrawGUI(BatchRenderer* _renderer, View& view) {
  if (!_viewingMap) {
    ///////////// Banners ///////////////

    for (GLuint player = 0; player < _numPlayers; player++) {
      if (player == _currentPlayer)
        _banner[player].SetScale(ENGINE::Vector2<float_type>(1.1, 1.1));
      else
        _banner[player].SetScale(ENGINE::Vector2<float_type>(1, 1));

      float_type xoff;
      float_type yoff;

      if (player % 2 == 0) {
        xoff = _hudSpacing;
        _banner[player].SetHorizontalAlign(HorzAlign::left);
      } else {
        xoff = RES_W - _banner[player].GetSize().x - _hudSpacing;
        _banner[player].SetHorizontalAlign(HorzAlign::right);
      }

      if (player < 2) {
        yoff = _hudSpacing;
        _banner[player].SetVerticalAlign(VertAlign::bottom);
      } else {
        yoff = RES_H - _banner[player].GetSize().y - _hudSpacing;
        _banner[player].SetVerticalAlign(VertAlign::top);
      }

      _banner[player].SetTranslation(ENGINE::Vector2<float_type>(xoff, yoff));
      _banner[player].Draw(_renderer, view);
    }
  } else {
    ///////////// View Arrows ///////////////

    View& globalView = ResourceManager::GetLevel("sutton").GetView();

    _arrowSprite.SetPivot(_arrowSprite.GetTextureSize() / 2);
    _arrowSprite.SetColor(_players[_currentPlayer].GetColor());

    if (globalView.GetTranslation().x > 0) {
      _arrowSprite.SetRotation(180);
      _arrowSprite.SetTranslation(ENGINE::Vector2<float_type>(0, RES_H / 2 - _arrowSprite.GetTextureSize().y / 2));
      _renderer->DrawSprite(_arrowSprite, view);
    }

    if (globalView.GetTranslation().x < (4400 - RES_W)) {
      _arrowSprite.SetRotation(0);
      _arrowSprite.SetTranslation(ENGINE::Vector2<float_type>(RES_W - _arrowSprite.GetTextureSize().x,
                                                              RES_H / 2 - _arrowSprite.GetTextureSize().y / 2));
      _renderer->DrawSprite(_arrowSprite, view);
    }

    if (globalView.GetTranslation().y > 0) {
      _arrowSprite.SetRotation(-90);
      _arrowSprite.SetTranslation(ENGINE::Vector2<float_type>((RES_W - _arrowSprite.GetTextureSize().y) / 2, 16));
      _renderer->DrawSprite(_arrowSprite, view);
    }

    if (globalView.GetTranslation().y < (2000 - RES_H)) {
      _arrowSprite.SetRotation(90);
      _arrowSprite.SetTranslation(ENGINE::Vector2<float_type>((RES_W - _arrowSprite.GetTextureSize().y) / 2,
                                                              RES_H - _arrowSprite.GetTextureSize().x + 16));
      _renderer->DrawSprite(_arrowSprite, view);
    }
  }

  ///////////// Wheel //////////////

  if (_donePlayerMoves) {
    _wheel.Draw(_renderer, view);
    _renderer->SetBlur(true);
  }

  ///////////// Keys ///////////////

  vector_t<string_t> keyNames;

  if (_donePlayerMoves) {
    if (!_wheel.GetStopped())
      keyNames.push_back("stop");

    else if (_wheel.GetSpinnerSpeed() == 0) {
      _renderer->SetBlur(false);
      ResourceManager::SetCurrentLevel("collect1");
    }
  } else {
    keyNames.push_back("item");
    keyNames.push_back("map");

    if (_players[_currentPlayer].GetNumberOfMoves() == 0) {
      keyNames.push_back("confirm");
      keyNames.push_back("cancel");
    }
  }

  if (!_viewingMap) {
    uint_t bannerLeftSize = _banner[(_numPlayers >= 3) ? 2 : 0].GetSize().x;
    uint_t bannerRightSize = _banner[(_numPlayers == 4) ? 3 : 1].GetSize().x;

    if (_numPlayers == 2) bannerRightSize = bannerLeftSize = std::min(bannerLeftSize, bannerRightSize);

    uint_t keyXSize = ResourceManager::GetSprite("keyicon").GetTextureSize().x;
    uint_t keyYSize = ResourceManager::GetSprite("keyicon").GetTextureSize().y;
    uint_t emptySpace = RES_W - (bannerLeftSize + bannerRightSize + (_hudSpacing * 2));
    uint_t keySpacing = (emptySpace - (keyXSize * keyNames.size())) / (keyNames.size() + 1);

    ENGINE::Vector2<float_type> keyPos(bannerLeftSize + keySpacing + _hudSpacing, RES_H - keyYSize - _hudSpacing);

    for (auto keyName : keyNames) {
      _keys.at(keyName).SetTranslation(keyPos);
      keyPos += ENGINE::Vector2<float_type>(keySpacing + keyXSize, 0);
      _keys.at(keyName).Draw(_renderer, view);
    }
  } else {
    KeyIcon& cancel = _keys.at("cancel");
    cancel.SetTranslation(
        ENGINE::Vector2<float_type>(RES_W - ResourceManager::GetSprite("keyicon").GetTextureSize().x - 150,
                                    RES_H - ResourceManager::GetSprite("keyicon").GetTextureSize().y - 50));

    cancel.Draw(_renderer, view);
  }
}

void ObjectHUD::Collision(CollisionInfo collision) {}

void ObjectHUD::PostCollision(float_type dt) {
  int_t hdir = 0;
  int_t vdir = 0;

  if (!_viewingMap && !_donePlayerMoves) {
    if (Input::ButtonPressed(GameControl::Right)) _players[_currentPlayer].MoveSpace(MapDirection::right);

    if (Input::ButtonPressed(GameControl::Left)) _players[_currentPlayer].MoveSpace(MapDirection::left);

    if (Input::ButtonPressed(GameControl::Up)) _players[_currentPlayer].MoveSpace(MapDirection::up);

    if (Input::ButtonPressed(GameControl::Down)) _players[_currentPlayer].MoveSpace(MapDirection::down);

    if (_players[_currentPlayer].GetNumberOfMoves() == 0 && Input::ButtonPressed(GameControl::A)) {
      if (_currentPlayer < _numPlayers - 1)
        _currentPlayer++;
      else {
        _donePlayerMoves = true;
        _currentPlayer = _playerTurn;
      }
    }

    if (Input::ButtonPressed(GameControl::B)) _players[_currentPlayer].UndoMoves();

    if (Input::ButtonPressed(GameControl::X)) _viewingMap = true;
  } else if (_viewingMap) {
    hdir = Input::ButtonHeld(GameControl::Right) - Input::ButtonHeld(GameControl::Left);
    vdir = Input::ButtonHeld(GameControl::Down) - Input::ButtonHeld(GameControl::Up);

    if (Input::ButtonPressed(GameControl::B)) _viewingMap = false;
  } else if (_donePlayerMoves) {
    if (Input::ButtonPressed(GameControl::A)) _wheel.SetStopped(true);
  }

  View& view = ResourceManager::GetLevel("sutton").GetView();

  if (!_viewingMap)
    view.SetTranslation(_players[_currentPlayer].GetBoardPosition() -
                        ENGINE::Vector2<float_type>(RES_W / 2, RES_H / 2));
  else
    view.Translate(ENGINE::Vector2<float_type>(hdir * _viewMapSpeed * dt, vdir * _viewMapSpeed * dt));

  view.SetTranslation(ENGINE::Vector2<float_type>(std::max(0.f, std::min(4400.f - RES_W, view.GetTranslation().x)),
                                                  std::max(0.f, std::min(2000.f - RES_H, view.GetTranslation().y))));

  for (auto& key : _keys) key.second.Update(dt);

  _wheel.Update(dt);
  _arrowSprite.UpdateFrame(dt);
}
