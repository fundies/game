#include "Atlas.hpp"
#include "ResourceManager.hpp"
#include "XMLParser.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

bool_t Atlas::LoadXML(const char_t* xmlFile, bool_t alpha) {
  try {
    XMLParser parser;

    if (!parser.Open(xmlFile)) return false;

    string_t textureFile = parser.Root->Attr.at("fileName")->GetString();
    ResourceManager::LoadTexture(getResPath("/textures/" + textureFile).c_str(), alpha, textureFile);
    SetTexture(ResourceManager::GetTexture(textureFile));

    for (auto imageTag : parser.Root->Child.at("image")) {
      string_t name = imageTag->Attr.at("fileName")->GetString();

      uint_t x = imageTag->Attr.at("x")->GetUnsigned();
      uint_t y = imageTag->Attr.at("y")->GetUnsigned();
      uint_t w = imageTag->Attr.at("width")->GetUnsigned();
      uint_t h = imageTag->Attr.at("height")->GetUnsigned();

      TextureQuad t(ENGINE::Vector2<float_type>(x, y), ENGINE::Vector2<float_type>(w, h));

      AddTextureQuad(name, t);
    }
  } catch (std::exception e) {
    PrintMessage("ERROR::ATLAS: Failed to read: %s", xmlFile);
    return false;
  }

  return true;
}

const ENGINE::Vector2<uint_t>& Atlas::GetSize() const { return _texture.GetSize(); }

void Atlas::Bind() { _texture.Bind(); }

void Atlas::SetTexture(const Texture2D& _texture) { this->_texture = _texture; }

void Atlas::AddTextureQuad(string_t name, const TextureQuad& quad) { _quads.emplace(name, quad); }

const TextureQuad& Atlas::GetTextureQuad(string_t name) const { return _quads.at(name); }

const umap_t<string_t, TextureQuad>& Atlas::GetQuads() const { return _quads; }
