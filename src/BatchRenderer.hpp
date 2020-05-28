#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "Atlas.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

#include <map>
#include <unordered_map>
#include <vector>

enum CAMERAMODE { CAMERA_SINGLE, CAMERA_GROUP, CAMERA_SPLIT };

class Text;

class GPUvert {
 public:
  GLint x = 0;
  GLint y = 0;
  GLint textureX = 0;
  GLint textureY = 0;
  GLubyte r = 255;
  GLubyte g = 255;
  GLubyte b = 255;
  GLubyte a = 255;
};

inline bool operator==(const GPUvert& lhs, const GPUvert& rhs){ 
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.textureX == rhs.textureX && lhs.textureY == rhs.textureY
  && lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

class BatchRenderer {
 public:
  BatchRenderer();
  ~BatchRenderer();
  void DrawSprite(const Sprite& spr);
  void DrawText(const Text& text, Color c = Color());
  void DrawLine(Vec2f a, Vec2f b, Color c = Color());
  void DrawCircle(Vec2f pos, float radius, Color c = Color(), size_t pointCount = 30);
  void DrawConvexShape(const ConvexShape& shape);
  void DrawConvexShape(const ConvexShape& shape, Color c);
  void MapData();
  void Draw();
  void Clear();
  void SetCoordSplit();
  void SetBlur(const bool& _blur);

 protected:
  void PushVert(const GPUvert& v);
  void initRenderData();
  unsigned _vao[2];
  unsigned _vbo[2];
  unsigned int framebuffer;
  unsigned int textureColorbuffer;
  unsigned int rbo;
  GLuint elementbuffer;
  
  std::vector<GPUvert> _coords;
  std::vector<unsigned int> _indexBuffer;
  unsigned _coordSplit;
  GPUvert vert[6];
  bool _blur;
  
  // Camera Stuff
  glm::mat4 GetProjection();
  CAMERAMODE _cameraMode;
  int _cameraHorPadding = 500;
  int _cameraVertPadding = 200;
  float _panSpeed = 0.02;
  float _zoomSpeed = 0.03;
  Vec2f _cameraPos;
  Vec2f _targetRes;
};

#endif
