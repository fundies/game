#include "Texture.hpp"
#include "ResourceManager.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

#include <SDL_image.h>

Texture2D::Texture2D() : _size(0, 0) { glGenTextures(1, &_ID); }

bool Texture2D::LoadImage(const char* imageFile, bool hasAlpha) {
  try {
    SDL_Surface* img = IMG_Load(imageFile);

    _size = Vec2u(img->w, img->h);

    glBindTexture(GL_TEXTURE_2D, _ID);
    //glObjectLabel(GL_TEXTURE, _ID, -1, std::to_string(ResourceManager::Textures.size()).c_str());
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, img->w, img->h, 0, hasAlpha ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(img);
  } catch (std::exception e) {
    PrintMessage("ERROR::IMAGE: Failed to read: %s %s %s", imageFile, IMG_GetError(), SDL_GetError());
    return false;
  }

  return true;
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, _ID); }

const unsigned& Texture2D::GetID() const { return _ID; }
const Vec2u& Texture2D::GetSize() const { return _size; }
