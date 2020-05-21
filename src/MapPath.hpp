#ifndef MAP_PATH_HPP
#define MAP_PATH_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class MapPath;

using mapPathPtr = std::shared_ptr<MapPath>;

class MapPath {
 public:
  MapPath(ENGINE::Vector2<int_t> position)
      : position(position), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}
  MapPath(ENGINE::Vector2<int_t> position, MapPath* left, MapPath* right, MapPath* up, MapPath* down)
      : position(position), left(left), right(right), up(up), down(down) {}

  ENGINE::Vector2<int_t> position;

  MapPath* left;
  MapPath* right;
  MapPath* up;
  MapPath* down;
};

#endif
