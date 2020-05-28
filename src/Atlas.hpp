#ifndef ATLAS_HPP
#define ATLAS_HPP

#include "Texture.hpp"
#include "TextureQuad.hpp"

class Atlas {
 public:
  Atlas() {}
  bool LoadXML(const char* xmlFile, bool alpha);
  void SetTexture(const Texture2D& _texture);
  void Bind();
  const Vec2u& GetSize() const;
  void AddTextureQuad(std::string name, const TextureQuad& quad);
  const TextureQuad& GetTextureQuad(std::string name) const;
  const std::unordered_map<std::string, TextureQuad>& GetQuads() const;

 protected:
  Texture2D _texture;
  std::unordered_map<std::string, TextureQuad> _quads;
};

#endif
