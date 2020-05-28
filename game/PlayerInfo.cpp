#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(std::string name, Color color, Sprite icon, Sprite mapIcon, MapPath* position)
    : _name(name), _color(color), _hudIcon(icon), _mapIcon(mapIcon), _mapPosition(position), _numberOfMoves(0) {}

void PlayerInfo::SetColor(const Color& _color) { this->_color = _color; }

void PlayerInfo::SetHUDIcon(const Sprite& _hudIcon) { this->_hudIcon = _hudIcon; }

void PlayerInfo::SetName(const std::string& _name) { this->_name = _name; }

const Color& PlayerInfo::GetColor() const { return _color; }

Sprite& PlayerInfo::GetHUDIcon() { return _hudIcon; }

const std::string& PlayerInfo::GetName() const { return _name; }

void PlayerInfo::SetMapIcon(const Sprite& _mapIcon) { this->_mapIcon = _mapIcon; }

Sprite& PlayerInfo::GetMapIcon() { return _mapIcon; }

bool PlayerInfo::SetMapPosition(MapPath* _mapPosition) {
  if (_mapPosition != nullptr) this->_mapPosition = _mapPosition;

  return (_mapPosition != nullptr);
}
const MapPath* PlayerInfo::GetMapPosition() const { return _mapPosition; }

const Vec2i& PlayerInfo::GetBoardPosition() const { return _mapPosition->position; }

void PlayerInfo::MoveSpace(MapDirection direction) {
  switch (direction) {
    case MapDirection::left: {
      if (_mapPosition->left != nullptr) {
        if (!_previousMoves.empty() && _previousMoves.top() == MapDirection::right) {
          _previousMoves.pop();
          _numberOfMoves++;
          SetMapPosition(_mapPosition->left);
        } else if (_numberOfMoves > 0) {
          _previousMoves.push(MapDirection::left);
          _numberOfMoves--;
          SetMapPosition(_mapPosition->left);
        }
      }

      break;
    }

    case MapDirection::right: {
      if (_mapPosition->right != nullptr) {
        if (!_previousMoves.empty() && _previousMoves.top() == MapDirection::left) {
          _previousMoves.pop();
          _numberOfMoves++;
          SetMapPosition(_mapPosition->right);
        } else if (_numberOfMoves > 0) {
          _previousMoves.push(MapDirection::right);
          _numberOfMoves--;
          SetMapPosition(_mapPosition->right);
        }
      }

      break;
    }

    case MapDirection::up: {
      if (_mapPosition->up != nullptr) {
        if (!_previousMoves.empty() && _previousMoves.top() == MapDirection::down) {
          _previousMoves.pop();
          _numberOfMoves++;
          SetMapPosition(_mapPosition->up);
        } else if (_numberOfMoves > 0) {
          _previousMoves.push(MapDirection::up);
          _numberOfMoves--;
          SetMapPosition(_mapPosition->up);
        }
      }

      break;
    }

    case MapDirection::down: {
      if (_mapPosition->down != nullptr) {
        if (!_previousMoves.empty() && _previousMoves.top() == MapDirection::up) {
          _previousMoves.pop();
          _numberOfMoves++;
          SetMapPosition(_mapPosition->down);
        } else if (_numberOfMoves > 0) {
          _previousMoves.push(MapDirection::down);
          _numberOfMoves--;
          SetMapPosition(_mapPosition->down);
        }
      }

      break;
    }
  }
}

void PlayerInfo::SetNumberOfMoves(const unsigned& _numberOfMoves) { this->_numberOfMoves = _numberOfMoves; }
const unsigned& PlayerInfo::GetNumberOfMoves() const { return _numberOfMoves; }

void PlayerInfo::UndoMoves() {
  while (!_previousMoves.empty()) {
    switch (_previousMoves.top()) {
      case MapDirection::right: {
        MoveSpace(MapDirection::left);
        break;
      }

      case MapDirection::left: {
        MoveSpace(MapDirection::right);
        break;
      }

      case MapDirection::up: {
        MoveSpace(MapDirection::down);
        break;
      }

      case MapDirection::down: {
        MoveSpace(MapDirection::up);
        break;
      }
    }
  }
}
