#ifndef MAP_PATH_HPP
#define MAP_PATH_HPP

#include "Types.hpp"
#include "Vector2.hpp"

class MapPath;

using mapPathPtr = std::shared_ptr<MapPath>;

class MapPath {
 public:
  MapPath(Vec2i position)
      : position(position), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}
  MapPath(Vec2i position, MapPath* left, MapPath* right, MapPath* up, MapPath* down)
      : position(position), left(left), right(right), up(up), down(down) {}

  Vec2i position;

  MapPath* left;
  MapPath* right;
  MapPath* up;
  MapPath* down;
};

#endif
