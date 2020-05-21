#ifndef ATLAS_HPP
#define ATLAS_HPP

#include "Texture.hpp"
#include "TextureQuad.hpp"

class Atlas {
 public:
  Atlas() {}
  bool_t LoadXML(const char_t* xmlFile, bool_t alpha);
  void SetTexture(const Texture2D& _texture);
  void Bind();
  const ENGINE::Vector2<uint_t>& GetSize() const;
  void AddTextureQuad(string_t name, const TextureQuad& quad);
  const TextureQuad& GetTextureQuad(string_t name) const;
  const umap_t<string_t, TextureQuad>& GetQuads() const;

 protected:
  Texture2D _texture;
  umap_t<string_t, TextureQuad> _quads;
};

#endif
