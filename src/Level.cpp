#include "Level.hpp"
#include "FileSystem.hpp"
#include "ResourceManager.hpp"
#include "FileUtil.hpp"

#include <algorithm>
#include <exception>

class TmxException : public std::exception {
  virtual const char_t* what() const throw() { return "Error reading map"; }
} tmxException;

int_t Level::gidClearFlags(uint_t gid) { return gid & TMX_FLIP_BITS_REMOVAL; }

uint_t Level::gidExtractFlags(uint_t gid) { return gid & ~TMX_FLIP_BITS_REMOVAL; }

void Level::LoadTMX(const char_t* fileName) {
  tmx_map* map = nullptr;

  try {
	const char* xml = FileRead(fileName);
    map = tmx_load_buffer(xml, strlen(xml));

    if (map == nullptr)
      throw tmxException;
    else
      ParseTMX(map);

    tmx_map_free(map);
  } catch (std::exception& e) {
    tmx_perror("tmx_load");
  }
}

void Level::ParseTMX(tmx_map* map) {
  string_t name;

  _size.x = map->tile_width * map->width;
  _size.y = map->tile_height * map->height;

  for (tmx_layer* layer = map->ly_head; layer != nullptr; layer = layer->next) {
    if (layer->type == L_IMAGE) {
      string_t tileName = remove_extension(base_name(string_t(layer->content.image->source)));
      Sprite spr = ResourceManager::GetSprite(tileName);

      _tiles.push_back(spr);

    } else if (layer->visible && layer->type == L_LAYER) {
      uint_t layerType = 0;

      if (layer->properties != nullptr) layerType = (tmx_get_property(layer->properties, "type"))->value.integer;

      for (uint_t i = 0; i < map->height; i++) {
        for (uint_t j = 0; j < map->width; j++) {
          uint_t tileID_l = layer->content.gids[(i * map->width) + j];
          uint_t tileID_s = gidClearFlags(tileID_l);

          if (map->tiles[tileID_s] != nullptr) {
            string_t tileName = remove_extension(base_name(string_t(map->tiles[tileID_s]->image->source)));
            uint_t tileFlags = gidExtractFlags(tileID_l);

            switch (layerType) {
              case 0: {
                break;
              }

              case 2: {
                SpaceDir thisSpace = GetSpaceProps(tileName, tileFlags);

                ENGINE::Vector2<int_t> currPos(j * map->tile_width, (i + 1) * map->tile_height - 100);
                mapPathPtr curr = findSpace(currPos);

                if (curr == nullptr) {
                  if (thisSpace.start) _boardStartIndex = spaces.size();

                  curr = mapPathPtr(new MapPath(ENGINE::Vector2<int_t>(j * map->tile_width, i * map->tile_height)));
                  spaces.push_back(curr);
                }

                unsigned leftID_l = (j > 0) ? layer->content.gids[(i * map->width) + (j - 1)] : 0;
                unsigned rightID_l = (j < map->width) ? layer->content.gids[(i * map->width) + (j + 1)] : 0;
                unsigned upID_l = (i > 0) ? layer->content.gids[((i - 1) * map->width) + j] : 0;
                unsigned downID_l = (i < map->height) ? layer->content.gids[((i + 1) * map->width) + j] : 0;

                if (leftID_l != 0) {
                  unsigned ID_s = gidClearFlags(leftID_l);
                  std::string otherName = remove_extension(base_name(std::string(map->tiles[ID_s]->image->source)));
                  unsigned otherFlags = gidExtractFlags(leftID_l);

                  SpaceDir otherSpace = GetSpaceProps(otherName, otherFlags);

                  if (thisSpace.left && otherSpace.right) {
                    ENGINE::Vector2<int_t> pos = currPos + ENGINE::Vector2<int_t>(-100, 0);

                    mapPathPtr left = findSpace(pos);

                    if (left == nullptr) {
                      left = mapPathPtr(new MapPath(pos, nullptr, curr.get(), nullptr, nullptr));
                      curr->left = left.get();
                      spaces.push_back(left);
                    } else {
                      curr->left = left.get();
                      curr->left->right = curr.get();
                    }
                  }
                }

                if (rightID_l != 0) {
                  unsigned ID_s = gidClearFlags(rightID_l);
                  std::string otherName = remove_extension(base_name(std::string(map->tiles[ID_s]->image->source)));
                  unsigned otherFlags = gidExtractFlags(rightID_l);

                  SpaceDir otherSpace = GetSpaceProps(otherName, otherFlags);

                  if (thisSpace.right && otherSpace.left) {
                    ENGINE::Vector2<int_t> pos = currPos + ENGINE::Vector2<int_t>(100, 0);

                    mapPathPtr right = findSpace(pos);

                    if (right == nullptr) {
                      right = mapPathPtr(new MapPath(pos, curr.get(), nullptr, nullptr, nullptr));
                      curr->right = right.get();
                      spaces.push_back(right);
                    } else {
                      curr->right = right.get();
                      curr->right->left = curr.get();
                    }
                  }
                }

                if (upID_l != 0) {
                  unsigned ID_s = gidClearFlags(upID_l);
                  std::string otherName = remove_extension(base_name(std::string(map->tiles[ID_s]->image->source)));
                  unsigned otherFlags = gidExtractFlags(upID_l);

                  SpaceDir otherSpace = GetSpaceProps(otherName, otherFlags);

                  if (thisSpace.up && otherSpace.down) {
                    ENGINE::Vector2<int_t> pos = currPos + ENGINE::Vector2<int_t>(0, -100);

                    mapPathPtr up = findSpace(pos);

                    if (up == nullptr) {
                      up = mapPathPtr(new MapPath(pos, nullptr, nullptr, nullptr, curr.get()));
                      curr->up = up.get();
                      spaces.push_back(up);
                    } else {
                      curr->up = up.get();
                      curr->up->down = curr.get();
                    }
                  }
                }

                if (downID_l != 0) {
                  unsigned ID_s = gidClearFlags(downID_l);
                  std::string otherName = remove_extension(base_name(std::string(map->tiles[ID_s]->image->source)));
                  unsigned otherFlags = gidExtractFlags(downID_l);

                  SpaceDir otherSpace = GetSpaceProps(otherName, otherFlags);

                  if (thisSpace.down && otherSpace.up) {
                    ENGINE::Vector2<int_t> pos = currPos + ENGINE::Vector2<int_t>(0, 100);

                    mapPathPtr down = findSpace(pos);

                    if (down == nullptr) {
                      down = mapPathPtr(new MapPath(pos, nullptr, nullptr, curr.get(), nullptr));
                      curr->down = down.get();
                      spaces.push_back(down);
                    } else {
                      curr->down = down.get();
                      curr->down->up = curr.get();
                    }
                  }
                }

                [[fallthrough]];
              }

              case 1: {
                std::bitset<3> tileFlips;
                tileFlips.set(0, tileFlags & TMX_FLIPPED_VERTICALLY);
                tileFlips.set(1, tileFlags & TMX_FLIPPED_HORIZONTALLY);
                tileFlips.set(2, tileFlags & TMX_FLIPPED_DIAGONALLY);

                Sprite spr = ResourceManager::GetSprite(tileName);

                spr.SetTranslation(ENGINE::Vector2<float_type>(j * map->tile_width,
                                                               (i + 1) * map->tile_height - spr.GetTextureSize().y));

                doFlips(tileFlips, &spr.GetPointM(0).GetTexturePositionM(), &spr.GetPointM(1).GetTexturePositionM(),
                        &spr.GetPointM(2).GetTexturePositionM(), &spr.GetPointM(3).GetTexturePositionM());

                _tiles.push_back(spr);

                break;
              }

              //Object
              case 3: {
                Transformation<float_type> t;

                std::bitset<3> bits;
                bits.set(0, tileFlags & TMX_FLIPPED_VERTICALLY);
                bits.set(1, tileFlags & TMX_FLIPPED_HORIZONTALLY);
                bits.set(2, tileFlags & TMX_FLIPPED_DIAGONALLY);

                //000 = no change
                //001 = vertical = swap y axis
                //010 = horizontal = swap x axis
                //011 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
                //100 = diag = rotate 90 degrees right and swap x axis
                //101 = diag+vert = rotate 270 degrees right
                //110 = horiz+diag = rotate 90 degrees right
                //111 = horiz+vert+diag = rotate 90 degrees right and swap y axis

                if (!bits.test(0) && !bits.test(1) && !bits.test(2)) {
                  //Shortcircuit tests for nothing to do
                  //return;
                } else if (bits.test(0) && !bits.test(1) && !bits.test(2)) {
                  //001
                  t.SetScale(ENGINE::Vector2<float_type>(1, -1));
                } else if (!bits.test(0) && bits.test(1) && !bits.test(2)) {
                  //010
                  t.SetScale(ENGINE::Vector2<float_type>(-1, 1));
                } else if (bits.test(0) && bits.test(1) && !bits.test(2)) {
                  //011
                  t.SetRotation(180);
                } else if (!bits.test(0) && !bits.test(1) && bits.test(2)) {
                  //100
                  t.SetRotation(90);
                  t.SetScale(ENGINE::Vector2<float_type>(-1, 1));
                } else if (bits.test(0) && !bits.test(1) && bits.test(2)) {
                  //101
                  t.SetRotation(270);
                } else if (!bits.test(0) && bits.test(1) && bits.test(2)) {
                  //110
                  t.SetRotation(90);
                } else if (bits.test(0) && bits.test(1) && bits.test(2)) {
                  //111
                  t.SetRotation(90);
                  t.SetScale(ENGINE::Vector2<float_type>(1, -1));
                }

                Sprite spr = ResourceManager::GetSprite(tileName);
                t.SetTranslation(ENGINE::Vector2<float_type>(j * map->tile_width,
                                                             (i + 1) * map->tile_height - spr.GetTextureSize().y));
                t.SetPivot(spr.GetCenter());

                AddInstance(tileName, t);

                break;
              }
            }
          }
        }
      }
    }
  }
}

void Level::doFlips(std::bitset<3> bits, ENGINE::Vector2<float_type>* v0, ENGINE::Vector2<float_type>* v1,
                    ENGINE::Vector2<float_type>* v2, ENGINE::Vector2<float_type>* v3) {
  //000 = no change
  //001 = vertical = swap y axis
  //010 = horizontal = swap x axis
  //011 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
  //100 = diag = rotate 90 degrees right and swap x axis
  //101 = diag+vert = rotate 270 degrees right
  //110 = horiz+diag = rotate 90 degrees right
  //111 = horiz+vert+diag = rotate 90 degrees right and swap y axis

  if (!bits.test(0) && !bits.test(1) && !bits.test(2)) {
    //Shortcircuit tests for nothing to do
    return;
  } else if (bits.test(0) && !bits.test(1) && !bits.test(2)) {
    //001
    flipY(v0, v1, v2, v3);
  } else if (!bits.test(0) && bits.test(1) && !bits.test(2)) {
    //010
    flipX(v0, v1, v2, v3);
  } else if (bits.test(0) && bits.test(1) && !bits.test(2)) {
    //011
    flipY(v0, v1, v2, v3);
    flipX(v0, v1, v2, v3);
  } else if (!bits.test(0) && !bits.test(1) && bits.test(2)) {
    //100
    flipD(v0, v1, v2, v3);
  } else if (bits.test(0) && !bits.test(1) && bits.test(2)) {
    //101
    flipX(v0, v1, v2, v3);
    flipD(v0, v1, v2, v3);

  } else if (!bits.test(0) && bits.test(1) && bits.test(2)) {
    //110
    flipY(v0, v1, v2, v3);
    flipD(v0, v1, v2, v3);

  } else if (bits.test(0) && bits.test(1) && bits.test(2)) {
    //111
    flipY(v0, v1, v2, v3);
    flipX(v0, v1, v2, v3);
    flipD(v0, v1, v2, v3);
  }
}

void Level::flipY(ENGINE::Vector2<float_type>* v0, ENGINE::Vector2<float_type>* v1, ENGINE::Vector2<float_type>* v2,
                  ENGINE::Vector2<float_type>* v3) {
  //Flip Y
  ENGINE::Vector2<float_type> tmp = *v0;
  v0->y = v2->y;
  v1->y = v2->y;
  v2->y = tmp.y;
  v3->y = v2->y;
}

void Level::flipX(ENGINE::Vector2<float_type>* v0, ENGINE::Vector2<float_type>* v1, ENGINE::Vector2<float_type>* v2,
                  ENGINE::Vector2<float_type>* v3) {
  //Flip X
  ENGINE::Vector2<float_type> tmp = *v0;
  v0->x = v1->x;
  v1->x = tmp.x;
  v2->x = v3->x;
  v3->x = v0->x;
}

void Level::flipD(ENGINE::Vector2<float_type>* v0, ENGINE::Vector2<float_type>* v1, ENGINE::Vector2<float_type>* v2,
                  ENGINE::Vector2<float_type>* v3) {
  //Diagonal flip
  ENGINE::Vector2<float_type> tmp = *v1;
  v1->x = v3->x;
  v1->y = v3->y;
  v3->x = tmp.x;
  v3->y = tmp.y;
}

void Level::SetGUIview(const View& _GUIview) { this->_GUIview = _GUIview; }

void Level::SetSize(const ENGINE::Vector2<uint_t>& _size) { this->_size = _size; }

void Level::SetTiles(const vector_t<Sprite>& _tiles) { this->_tiles = _tiles; }

void Level::SetView(const View& _view) { this->_view = _view; }

View& Level::GetGUIview() { return _GUIview; }

const ENGINE::Vector2<uint_t>& Level::GetSize() const { return _size; }

const vector_t<Sprite>& Level::GetTiles() const { return _tiles; }

View& Level::GetView() { return _view; }

SpaceDir Level::GetSpaceProps(std::string spaceType, unsigned flags) {
  bool canLeft = false;
  bool canRight = false;
  bool canUp = false;
  bool canDown = false;
  bool start = (spaceType == "space_start");

  bool flipHorz = flags & TMX_FLIPPED_HORIZONTALLY;
  bool flipVert = flags & TMX_FLIPPED_VERTICALLY;
  bool flipDiag = flags & TMX_FLIPPED_DIAGONALLY;

  if (spaceType == "line +" || spaceType == "space_start" || spaceType == "space_goal" || spaceType == "map start") {
    canLeft = true;
    canRight = true;
    canUp = true;
    canDown = true;
  }

  if (spaceType == "line end") {
    if (!flipVert && !flipHorz && !flipDiag) {
      // default
      canLeft = true;
    } else if (flipVert && !flipHorz && !flipDiag) {
      // flip vertical
      canLeft = true;
    }

    else if (!flipVert && flipHorz && !flipDiag) {
      // flip horizontal
      canRight = true;
    }

    else if (flipVert && flipHorz && !flipDiag) {
      // rotate 180
      canRight = true;
    }

    else if (!flipVert && !flipHorz && flipDiag) {
      // rotate 90 & flip horizontal
      canUp = true;
    }

    else if (flipVert && !flipHorz && flipDiag) {
      // rotate 270
      canDown = true;
    }

    else if (!flipVert && flipHorz && flipDiag) {
      // rotate 90
      canUp = true;
    }

    else if (flipVert && flipHorz && flipDiag) {
      // rotate 90 & flip vertical
      canDown = true;
    }
  }

  if (spaceType == "line hor") {
    if (!flipVert && !flipHorz && !flipDiag) {
      // default
      canLeft = true;
      canRight = true;
    } else if (flipVert && !flipHorz && !flipDiag) {
      // flip vertical
      canLeft = true;
      canRight = true;
    }

    else if (!flipVert && flipHorz && !flipDiag) {
      // flip horizontal
      canRight = true;
      canLeft = true;
    }

    else if (flipVert && flipHorz && !flipDiag) {
      // rotate 180
      canRight = true;
      canLeft = true;
    }

    else if (!flipVert && !flipHorz && flipDiag) {
      // rotate 90 & flip horizontal
      canUp = true;
      canDown = true;
    }

    else if (flipVert && !flipHorz && flipDiag) {
      // rotate 270
      canDown = true;
      canUp = true;
    }

    else if (!flipVert && flipHorz && flipDiag) {
      // rotate 90
      canUp = true;
      canDown = true;
    }

    else if (flipVert && flipHorz && flipDiag) {
      // rotate 90 & flip vertical
      canDown = true;
      canUp = true;
    }
  }

  if (spaceType == "line L") {
    if (!flipVert && !flipHorz && !flipDiag) {
      // default
      canLeft = true;
      canDown = true;
    } else if (flipVert && !flipHorz && !flipDiag) {
      // flip vertical
      canLeft = true;
      canUp = true;
    }

    else if (!flipVert && flipHorz && !flipDiag) {
      // flip horizontal
      canRight = true;
      canDown = true;
    }

    else if (flipVert && flipHorz && !flipDiag) {
      // rotate 180
      canRight = true;
      canUp = true;
    }

    else if (!flipVert && !flipHorz && flipDiag) {
      // rotate 90 & flip horizontal
      canRight = true;
      canUp = true;
    }

    else if (flipVert && !flipHorz && flipDiag) {
      // rotate 270
      canRight = true;
      canDown = true;
    }

    else if (!flipVert && flipHorz && flipDiag) {
      // rotate 90
      canLeft = true;
      canUp = true;
    }

    else if (flipVert && flipHorz && flipDiag) {
      // rotate 90 & flip vertical
      canRight = true;
      canDown = true;
    }
  }

  if (spaceType == "line T") {
    if (!flipVert && !flipHorz && !flipDiag) {
      // default
      canLeft = true;
      canRight = true;
      canDown = true;
    } else if (flipVert && !flipHorz && !flipDiag) {
      // flip vertical
      canLeft = true;
      canRight = true;
      canUp = true;
    }

    else if (!flipVert && flipHorz && !flipDiag) {
      // flip horizontal
      canLeft = true;
      canRight = true;
      canDown = true;
    }

    else if (flipVert && flipHorz && !flipDiag) {
      // rotate 180
      canLeft = true;
      canRight = true;
      canUp = true;
    }

    else if (!flipVert && !flipHorz && flipDiag) {
      // rotate 90 & flip horizontal
      canUp = true;
      canDown = true;
      canRight = true;
    }

    else if (flipVert && !flipHorz && flipDiag) {
      // rotate 270
      canUp = true;
      canDown = true;
      canRight = true;
    }

    else if (!flipVert && flipHorz && flipDiag) {
      // rotate 90
      canUp = true;
      canDown = true;
      canLeft = true;
    }

    else if (flipVert && flipHorz && flipDiag) {
      // rotate 90 & flip vertical
      canUp = true;
      canDown = true;
      canLeft = true;
    }
  }

  return SpaceDir(canLeft, canRight, canUp, canDown, start);
}

mapPathPtr Level::findSpace(ENGINE::Vector2<int_t> space) {
  auto it = std::find_if(std::begin(spaces), std::end(spaces),
                         [&space](mapPathPtr path) { return (path->position == space); });

  if (it != std::end(spaces))
    return *it;
  else
    return nullptr;
}

MapPath* Level::GetBoardSpace(uint_t index) { return spaces[index].get(); }

MapPath* Level::GetBoardStartSpace() { return GetBoardSpace(_boardStartIndex); }

const vector_t<Instance>& Level::GetInstances() const { return _instances; }

const vector_t<Instance>& Level::GetInstancesFollowing() const { return _instancesFollowing; }

#include "ObjectBlock.hpp"
#include "ObjectBlockHalf.hpp"
#include "ObjectCollectible.hpp"
#include "ObjectHUD.hpp"
#include "ObjectHill1.hpp"
#include "ObjectHill2.hpp"
#include "ObjectHill3.hpp"
#include "ObjectPlayer.hpp"
#include "ObjectPlayerSelect.hpp"
Instance Level::AddInstance(string_t name, Transformation<float_type> t) {
  Instance inst = nullptr;

  if (name == "HUD")
    inst = ObjectHUD::Create(t);
  else if (name == "block")
    inst = ObjectBlock::Create(t);
  else if (name == "block half")
    inst = ObjectBlockHalf::Create(t);
  else if (name == "hill_1")
    inst = ObjectHill1::Create(t);
  else if (name == "hill_2")
    inst = ObjectHill2::Create(t);
  else if (name == "hill_3")
    inst = ObjectHill3::Create(t);
  else if (name == "collectible")
    inst = ObjectCollectible::Create(t);
  else if (name == "mask_greg") {
    inst = ObjectPlayer::Create(t);
    _instancesFollowing.push_back(inst);
  } else if (name == "PlayerSelect")
    inst = ObjectPlayerSelect::Create(t);

  if (inst != nullptr) _instances.push_back(inst);

  return inst;
}
