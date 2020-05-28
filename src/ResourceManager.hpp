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
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  static std::map<std::string, Atlas> Atlases;
  static std::map<std::string, Sprite> Sprites;
  static std::map<std::string, Mask> Masks;
  static std::map<std::string, Level> Levels;
  static Level* CurrentLevel;

  static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile,
                            std::string name);
  static Shader& GetShader(std::string name);

  static Texture2D& LoadTexture(const char* file, bool alpha, std::string name);
  static Texture2D& GetTexture(std::string name);

  static Atlas& LoadAtlas(const char* file, bool alpha, std::string name);
  static Atlas& GetAtlas(std::string name);

  static const Sprite LoadSprite(const char* file);
  static const Sprite GetSprite(std::string name);

  static const Mask LoadMask(const char* file, std::string name);
  static const Mask GetMask(std::string name);

  static Level& CreateLevel(std::string name, CAMERAMODE mode);
  static Level& LoadLevel(const char* file, std::string name, CAMERAMODE mode);
  static Level& GetLevel(std::string name);

  static void SetCurrentLevel(std::string name);
  static Level* GetCurrentLevel();

  static void Clear();

 protected:
  ResourceManager() {}
};

#endif
