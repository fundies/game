#include "ResourceManager.hpp"
#include "FileSystem.hpp"
#include "XMLParser.hpp"
#include "Logger.hpp"

map_t<string_t, Texture2D> ResourceManager::Textures;
map_t<string_t, Shader> ResourceManager::Shaders;
map_t<string_t, Atlas> ResourceManager::Atlases;
map_t<string_t, Sprite> ResourceManager::Sprites;
map_t<string_t, Mask> ResourceManager::Masks;
map_t<string_t, Level> ResourceManager::Levels;
Level* ResourceManager::CurrentLevel;

Shader& ResourceManager::LoadShader(const char_t* vShaderFile, const char_t* fShaderFile, const char_t* gShaderFile,
                                    string_t name) {
  Shader shader;
  shader.LoadShaderFile(vShaderFile, fShaderFile, gShaderFile);

  Shaders[name] = shader;

  return Shaders[name];
}

Shader& ResourceManager::GetShader(string_t name) { return Shaders[name]; }

Texture2D& ResourceManager::LoadTexture(const char_t* file, bool_t alpha, string_t name) {
  Texture2D texture;
  texture.LoadImage(file, alpha);

  Textures[name] = texture;
  return Textures[name];
}

Texture2D& ResourceManager::GetTexture(string_t name) { return Textures[name]; }

Atlas& ResourceManager::LoadAtlas(const char_t* file, bool_t alpha, string_t name) {
  Atlas atlas;
  atlas.LoadXML(file, true);

  for (const auto& q : atlas.GetQuads()) {
    Sprite spr(q.second);
    Sprites.emplace(q.first, spr);
  }

  Atlases.emplace(name, atlas);

  return Atlases.at(name);
}

Atlas& ResourceManager::GetAtlas(string_t name) { return Atlases[name]; }

const Sprite ResourceManager::LoadSprite(const char_t* file) {
  Sprite spr;
  string_t name;

  try {
    XMLParser parser;

    if (!parser.Open(file)) {
      PrintMessage("ERROR::SPRITE: Failed to read: %s", file);
      return spr;
    }

    parser.Parse();

    name = parser.Root->Attr.at("name")->GetString();
    float_type speed = parser.Root->Attr.at("speed")->GetFloat();

    spr.SetAnimationSpeed(speed);

    for (auto frameTag : parser.Root->Child.at("frame")) {
      string_t src = remove_extension(frameTag->Attr.at("src")->GetString());
      spr.AddFrame(ResourceManager::GetAtlas("test").GetTextureQuad(src));
    }
  } catch (std::exception e) {
    PrintMessage("ERROR::SPRITE: Failed to parse: %s", file);
    return spr;
  }

  Sprites.emplace(name, spr);

  return Sprites.at(name);
}

const Sprite ResourceManager::GetSprite(string_t name) {
  try {
    return Sprites.at(name);
  } catch (std::exception e) {
    PrintMessage("ERROR::SPRITE: Lookup failed for: %s", name.c_str());
    return Sprite();
  }
}

const Mask ResourceManager::LoadMask(const char_t* file, string_t name) {
  Mask m;
  m.LoadXML(file);

  Masks[name] = m;

  return Masks[name];
}

const Mask ResourceManager::GetMask(string_t name) { return Masks[name]; }

Level& ResourceManager::CreateLevel(string_t name, CAMERAMODE mode) {
  Level lvl(mode);

  Levels[name] = lvl;

  return Levels[name];
}

Level& ResourceManager::LoadLevel(const char_t* file, string_t name, CAMERAMODE mode) {
  Level lvl(mode);
  lvl.LoadTMX(file);

  Levels[name] = lvl;

  return Levels[name];
}

Level& ResourceManager::GetLevel(string_t name) { return Levels[name]; }

void ResourceManager::Clear() {
  // (Properly) delete all shaders
  for (auto iter : Shaders) glDeleteProgram(iter.second.GetID());

  // (Properly) delete all textures
  for (auto iter : Textures) glDeleteTextures(1, &iter.second.GetID());
}

void ResourceManager::SetCurrentLevel(string_t name) { CurrentLevel = &Levels.at(name); }

Level* ResourceManager::GetCurrentLevel() { return CurrentLevel; }
