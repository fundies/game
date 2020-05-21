#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "Atlas.hpp"
#include "Level.hpp"
#include "Object.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Types.hpp"

class ResourceManager {
 public:
  static map_t<string_t, Shader> Shaders;
  static map_t<string_t, Texture2D> Textures;
  static map_t<string_t, Atlas> Atlases;
  static map_t<string_t, Sprite> Sprites;
  static map_t<string_t, Mask> Masks;
  static map_t<string_t, Level> Levels;
  static Level* CurrentLevel;

  static Shader& LoadShader(const char_t* vShaderFile, const char_t* fShaderFile, const char_t* gShaderFile,
                            string_t name);
  static Shader& GetShader(string_t name);

  static Texture2D& LoadTexture(const char_t* file, bool_t alpha, string_t name);
  static Texture2D& GetTexture(string_t name);

  static Atlas& LoadAtlas(const char_t* file, bool_t alpha, string_t name);
  static Atlas& GetAtlas(string_t name);

  static const Sprite LoadSprite(const char_t* file);
  static const Sprite GetSprite(string_t name);

  static const Mask LoadMask(const char_t* file, string_t name);
  static const Mask GetMask(string_t name);

  static Level& CreateLevel(string_t name, CAMERAMODE mode);
  static Level& LoadLevel(const char_t* file, string_t name, CAMERAMODE mode);
  static Level& GetLevel(string_t name);

  static void SetCurrentLevel(string_t name);
  static Level* GetCurrentLevel();

  static void Clear();

 protected:
  ResourceManager() {}
};

#endif
