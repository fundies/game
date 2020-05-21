#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include "Color.hpp"
#include "MapPath.hpp"
#include "Sprite.hpp"

#include <stack>

enum class MapDirection : uint_t { left, right, up, down };

class PlayerInfo {
 public:
  PlayerInfo(std::string name, Color color, Sprite icon, Sprite mapIcon, MapPath* position);
  void SetColor(const Color& _color);
  void SetHUDIcon(const Sprite& _hudIcon);
  void SetName(const std::string& _name);
  const Color& GetColor() const;
  Sprite& GetHUDIcon();
  const std::string& GetName() const;
  void SetMapIcon(const Sprite& _mapIcon);
  Sprite& GetMapIcon();
  bool_t SetMapPosition(MapPath* _mapPosition);
  const MapPath* GetMapPosition() const;
  const ENGINE::Vector2<int_t>& GetBoardPosition() const;
  void MoveSpace(MapDirection direction);
  void SetNumberOfMoves(const uint_t& _numberOfMoves);
  const uint_t& GetNumberOfMoves() const;
  void UndoMoves();

 protected:
  std::string _name;
  Color _color;
  Sprite _hudIcon;
  Sprite _mapIcon;
  MapPath* _mapPosition;
  uint_t _numberOfMoves;
  std::stack<MapDirection> _previousMoves;
};

#endif
