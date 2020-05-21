#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "Atlas.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "View.hpp"

#include <map>
#include <vector>

enum CAMERAMODE { CAMERA_SINGLE, CAMERA_GROUP, CAMERA_SPLIT };

class Text;

class GPUvert {
 public:
  GLshort x = 0;
  GLshort y = 0;
  GLshort textureX = 0;
  GLshort textureY = 0;
  GLubyte r = 255;
  GLubyte g = 255;
  GLubyte b = 255;
  GLubyte a = 255;
};

class BatchRenderer {
 public:
  BatchRenderer();
  ~BatchRenderer();
  void DrawSprite(const Sprite& spr, const View& view);
  void DrawText(const Text& text, const View& view);
  void DrawConvexShape(const ConvexShape& shape, const View& view);
  void MapData();
  void Draw();
  void Clear();
  void SetCoordSplit();
  void SetBlur(const bool_t& _blur);

 protected:
  void initRenderData();
  uint_t _vao[2];
  uint_t _vbo[2];
  uint_t _framebuffer[2];
  uint_t _renderTexture[2];
  vector_t<GPUvert> _coords;
  uint_t _coordSplit;
  GPUvert vert[6];
  bool_t _blur;
  CAMERAMODE _cameraMode;
  ENGINE::Vector2<float_t> _cameraPos;
  ENGINE::Vector2<float_t> _idealRes;
  float_t _cameraZoom = 1;
};

#endif
