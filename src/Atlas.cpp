#include "Atlas.hpp"
#include "ResourceManager.hpp"
#include "XMLParser.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

bool Atlas::LoadXML(const char* xmlFile, bool alpha) {
  try {
    XMLParser parser;

    if (!parser.Open(xmlFile)) return false;

    std::string textureFile = parser.Root->Attr.at("fileName")->GetString();
    ResourceManager::LoadTexture(getResPath("/textures/" + textureFile).c_str(), alpha, textureFile);
    SetTexture(ResourceManager::GetTexture(textureFile));

    for (auto imageTag : parser.Root->Child.at("image")) {
      std::string name = imageTag->Attr.at("fileName")->GetString();

      unsigned x = imageTag->Attr.at("x")->GetUnsigned();
      unsigned y = imageTag->Attr.at("y")->GetUnsigned();
      unsigned w = imageTag->Attr.at("width")->GetUnsigned();
      unsigned h = imageTag->Attr.at("height")->GetUnsigned();

      TextureQuad t(Vec2f(x, y), Vec2f(w, h));

      AddTextureQuad(name, t);
    }
  } catch (std::exception e) {
    PrintMessage("ERROR::ATLAS: Failed to read: %s", xmlFile);
    return false;
  }

  return true;
}

const Vec2u& Atlas::GetSize() const { return _texture.GetSize(); }

void Atlas::Bind() { _texture.Bind(); }

void Atlas::SetTexture(const Texture2D& _texture) { this->_texture = _texture; }

void Atlas::AddTextureQuad(std::string name, const TextureQuad& quad) { _quads.emplace(name, quad); }

const TextureQuad& Atlas::GetTextureQuad(std::string name) const { return _quads.at(name); }

const std::unordered_map<std::string, TextureQuad>& Atlas::GetQuads() const { return _quads; }
