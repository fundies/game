#include "ResourceManager.hpp"
#include "FileSystem.hpp"
#include "XMLParser.hpp"
#include "Logger.hpp"

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Atlas> ResourceManager::Atlases;
std::map<std::string, Sprite> ResourceManager::Sprites;
std::map<std::string, Mask> ResourceManager::Masks;
std::map<std::string, Level> ResourceManager::Levels;
Level* ResourceManager::CurrentLevel;

Shader& ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile,
                                    std::string name) {
  Shader shader;
  shader.LoadShaderFile(vShaderFile, fShaderFile, gShaderFile);

  Shaders[name] = shader;

  return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name) { return Shaders[name]; }

Texture2D& ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
  Texture2D texture;
  texture.LoadImage(file, alpha);

  Textures[name] = texture;
  return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name) { return Textures[name]; }

Atlas& ResourceManager::LoadAtlas(const char* file, bool alpha, std::string name) {
  Atlas atlas;
  atlas.LoadXML(file, true);

  for (const auto& q : atlas.GetQuads()) {
    Sprite spr(q.second);
    Sprites.emplace(q.first, spr);
  }

  Atlases.emplace(name, atlas);

  return Atlases.at(name);
}

Atlas& ResourceManager::GetAtlas(std::string name) { return Atlases[name]; }

const Sprite ResourceManager::LoadSprite(const char* file) {
  Sprite spr;
  std::string name;

  try {
    XMLParser parser;

    if (!parser.Open(file)) {
      PrintMessage("ERROR::SPRITE: Failed to read: %s", file);
      return spr;
    }

    parser.Parse();

    name = parser.Root->Attr.at("name")->GetString();
    float speed = parser.Root->Attr.at("speed")->GetFloat();

    spr.SetAnimationSpeed(speed);

    for (auto frameTag : parser.Root->Child.at("frame")) {
      std::string src = remove_extension(frameTag->Attr.at("src")->GetString());
      spr.AddFrame(ResourceManager::GetAtlas("test").GetTextureQuad(src));
    }
  } catch (std::exception e) {
    PrintMessage("ERROR::SPRITE: Failed to parse: %s", file);
    return spr;
  }

  Sprites.emplace(name, spr);

  return Sprites.at(name);
}

const Sprite ResourceManager::GetSprite(std::string name) {
  try {
    return Sprites.at(name);
  } catch (std::exception e) {
    PrintMessage("ERROR::SPRITE: Lookup failed for: %s", name.c_str());
    return Sprite();
  }
}

const Mask ResourceManager::LoadMask(const char* file, std::string name) {
  Mask m;
  m.LoadXML(file);

  Masks[name] = m;

  return Masks[name];
}

const Mask ResourceManager::GetMask(std::string name) { return Masks[name]; }

Level& ResourceManager::CreateLevel(std::string name, CAMERAMODE mode) {
  Level lvl(mode);

  Levels[name] = lvl;

  return Levels[name];
}

Level& ResourceManager::LoadLevel(const char* file, std::string name, CAMERAMODE mode) {
  Level lvl(mode);
  lvl.LoadTMX(file);

  Levels[name] = lvl;

  return Levels[name];
}

Level& ResourceManager::GetLevel(std::string name) { return Levels[name]; }

void ResourceManager::Clear() {
  // (Properly) delete all shaders
  for (auto iter : Shaders) glDeleteProgram(iter.second.GetID());

  // (Properly) delete all textures
  for (auto iter : Textures) glDeleteTextures(1, &iter.second.GetID());
}

void ResourceManager::SetCurrentLevel(std::string name) { CurrentLevel = &Levels.at(name); }

Level* ResourceManager::GetCurrentLevel() { return CurrentLevel; }
