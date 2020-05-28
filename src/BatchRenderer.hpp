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
  unsigned char r = 255;
  unsigned char g = 255;
  unsigned char b = 255;
  unsigned char a = 255;
};

inline bool operator==(const GPUvert& lhs, const GPUvert& rhs){ 
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.textureX == rhs.textureX && lhs.textureY == rhs.textureY
  && lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

namespace hash_detail {

/**
 * @brief The prime to use for the FNVa hash algorithm, as a type trait.
 */
template <typename UInt>
struct fnv_prime;

template <>
struct fnv_prime<std::uint32_t>
    : std::integral_constant<std::uint32_t, 16777619ul> {};
template <>
struct fnv_prime<std::uint64_t>
    : std::integral_constant<std::uint64_t, 1099511628211ull> {};

template <typename UInt>
struct fnv_prime {
    constexpr static UInt value = (sizeof(UInt) == sizeof(std::uint64_t)
                                       ? fnv_prime<std::uint64_t>::value
                                       : fnv_prime<std::uint32_t>::value);
};

/**
 * @brief The starting value for the FNVa hash algorithm, as a type trait.
 */
template <typename UInt>
struct fnv_offset;

template <>
struct fnv_offset<std::uint32_t>
    : std::integral_constant<std::uint32_t, 2166136261ul> {};
template <>
struct fnv_offset<std::uint64_t>
    : std::integral_constant<std::uint64_t, 14695981039346656037ull> {};

template <typename UInt>
struct fnv_offset {
    constexpr static UInt value = (sizeof(UInt) == sizeof(std::uint64_t)
                                       ? fnv_offset<std::uint64_t>::value
                                       : fnv_offset<std::uint32_t>::value);
};

} // namespace hash_detail

struct hash {
    static_assert(sizeof(GPUvert) == sizeof(int) * 4 + 4);
    std::size_t operator()(const GPUvert& x) const {
        constexpr std::size_t prime = hash_detail::fnv_prime<std::size_t>::value;
        std::size_t hval = hash_detail::fnv_offset<std::size_t>::value;
        auto begin = reinterpret_cast<const char*>(&x);
        for (unsigned char c : std::string_view{begin, sizeof(x)}) {
            hval ^= static_cast<std::size_t>(c);
            hval *= prime;
        }
        return hval;
    }
};

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
  
  std::unordered_map<GPUvert, size_t, hash> _coordMap;
  std::vector<GPUvert*> _coordOrder;
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
