#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Atlas.hpp"
#include "MapPath.hpp"
#include "Object.hpp"
#include "Sprite.hpp"
#include "View.hpp"

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
  void LoadTMX(const char_t *fileName);
  void ParseTMX(tmx_map *map);

  void SetGUIview(const View &_GUIview);
  void SetSize(const ENGINE::Vector2<uint_t> &_size);
  void SetTiles(const vector_t<Sprite> &_tiles);
  void SetView(const View &_view);
  View &GetGUIview();
  const ENGINE::Vector2<uint_t> &GetSize() const;
  const vector_t<Sprite> &GetTiles() const;
  View &GetView();
  MapPath *GetBoardSpace(uint_t index);
  MapPath *GetBoardStartSpace();
  const vector_t<Instance> &GetInstances() const;
  const vector_t<Instance> &GetInstancesFollowing() const;
  Instance AddInstance(string_t name, Transformation<float_type> t);

 protected:
  CAMERAMODE _cameraMode;
  int_t gidClearFlags(uint_t gid);
  uint_t gidExtractFlags(uint_t gid);

  void doFlips(std::bitset<3> bits, ENGINE::Vector2<float_type> *v0, ENGINE::Vector2<float_type> *v1,
               ENGINE::Vector2<float_type> *v2, ENGINE::Vector2<float_type> *v3);
  void flipY(ENGINE::Vector2<float_type> *v0, ENGINE::Vector2<float_type> *v1, ENGINE::Vector2<float_type> *v2,
             ENGINE::Vector2<float_type> *v3);
  void flipX(ENGINE::Vector2<float_type> *v0, ENGINE::Vector2<float_type> *v1, ENGINE::Vector2<float_type> *v2,
             ENGINE::Vector2<float_type> *v3);
  void flipD(ENGINE::Vector2<float_type> *v0, ENGINE::Vector2<float_type> *v1, ENGINE::Vector2<float_type> *v2,
             ENGINE::Vector2<float_type> *v3);

  SpaceDir GetSpaceProps(std::string spaceType, unsigned flags);
  mapPathPtr findSpace(ENGINE::Vector2<int_t> position);

  vector_t<Instance> _instances;
  vector_t<Instance> _instancesFollowing;

  ENGINE::Vector2<uint_t> _size;
  vector_t<Sprite> _tiles;
  View _view;
  View _GUIview;

  vector_t<mapPathPtr> spaces;
  uint_t _boardStartIndex = 0;
};

#endif
