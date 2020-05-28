#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Atlas.hpp"
#include "MapPath.hpp"
#include "Object.hpp"
#include "Sprite.hpp"

#include <tmx.h>
#include <bitset>
#include <vector>

class SpaceDir {
 public:
  SpaceDir(bool left, bool right, bool up, bool down, bool start)
      : left(left), right(right), up(up), down(down), start(start) {}

  bool left;
  bool right;
  bool up;
  bool down;
  bool start;
};

class Level {
 public:
  Level() : _cameraMode(CAMERAMODE::CAMERA_SINGLE) {}
  Level(CAMERAMODE mode) : _cameraMode(mode) {}
  void LoadTMX(const char *fileName);
  void ParseTMX(tmx_map *map);

  void SetSize(const Vec2u &_size);
  void SetTiles(const std::vector<Sprite> &_tiles);
  const Vec2u &GetSize() const;
  const std::vector<Sprite> &GetTiles() const;
  MapPath *GetBoardSpace(unsigned index);
  MapPath *GetBoardStartSpace();
  const std::vector<Instance> &GetInstances() const;
  const std::vector<Instance> &GetInstancesFollowing() const;
  Instance AddInstance(std::string name, Transformation<float> t);

 protected:
  CAMERAMODE _cameraMode;
  int gidClearFlags(unsigned gid);
  unsigned gidExtractFlags(unsigned gid);

  void doFlips(std::bitset<3> bits, Vec2f *v0, Vec2f *v1,
               Vec2f *v2, Vec2f *v3);
  void flipY(Vec2f *v0, Vec2f *v1, Vec2f *v2,
             Vec2f *v3);
  void flipX(Vec2f *v0, Vec2f *v1, Vec2f *v2,
             Vec2f *v3);
  void flipD(Vec2f *v0, Vec2f *v1, Vec2f *v2,
             Vec2f *v3);

  SpaceDir GetSpaceProps(std::string spaceType, unsigned flags);
  mapPathPtr findSpace(Vec2i position);

  std::vector<Instance> _instances;
  std::vector<Instance> _instancesFollowing;

  Vec2u _size;
  std::vector<Sprite> _tiles;

  std::vector<mapPathPtr> spaces;
  unsigned _boardStartIndex = 0;
};

#endif
