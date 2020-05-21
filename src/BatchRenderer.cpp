#include "BatchRenderer.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Text.hpp"
#include "Logger.hpp"

#include <cstring>

#ifndef glDeleteVertexArrays
 #define glDeleteVertexArrays glDeleteVertexArraysOES
 #define glBindVertexArray glBindVertexArrayOES
 #define glGenVertexArrays glGenVertexArraysOES
 #define glDrawBuffers glDrawBuffersEXT
#endif

BatchRenderer::BatchRenderer() : _blur(false), _cameraMode(CAMERAMODE::CAMERA_SINGLE), _idealRes(1920,1080) { initRenderData(); }

BatchRenderer::~BatchRenderer() {
  glDeleteVertexArrays(1, &_vao[0]);
  glDeleteVertexArrays(1, &_vao[1]);
}

void BatchRenderer::DrawSprite(const Sprite& spr, const View& view) { DrawConvexShape(spr, view); }

void BatchRenderer::DrawText(const Text& text, const View& view) {
  for (const auto& letter : text.GetLetters()) {
    if (text.GetShadowPosition() != ENGINE::Vector2<float_type>(0, 0)) {
      Sprite t = letter;
      t.SetScale(letter.GetScale() * text.GetScale());
      t.SetRotation(letter.GetRotation() + text.GetRotation());
      t.SetTranslation(letter.GetTranslation() + text.GetTranslation() + text.GetShadowPosition());
      t.SetColor(text.GetShadowColor());

      DrawSprite(t, view);
    }

    Sprite t = letter;
    t.SetScale(letter.GetScale() * text.GetScale());
    t.SetRotation(letter.GetRotation() + text.GetRotation());
    t.SetTranslation(letter.GetTranslation() + text.GetTranslation());

    DrawSprite(t, view);
  }
}

void BatchRenderer::DrawConvexShape(const ConvexShape& shape, const View& view) {
  uint_t count = shape.GetPointCount();

  if (count < 3) return;

  /*ConvexShape ViewQuad(4);
	ViewQuad.SetPoint(0, Vertex(ENGINE::Vector2<float_t>(-view.GetPosition().x, -view.GetPosition().y)));
	ViewQuad.SetPoint(1, Vertex(ENGINE::Vector2<float_t>(-view.GetPosition().x + 1920, -view.GetPosition().y)));
	ViewQuad.SetPoint(2, Vertex(ENGINE::Vector2<float_t>(-view.GetPosition().x + 1920, view.GetPosition().y + 1080)));
	ViewQuad.SetPoint(3, Vertex(ENGINE::Vector2<float_t>(-view.GetPosition().x, -view.GetPosition().y + 1080)));*/

  // if (!ViewQuad.AABB(shape))
  // return;

  if (count == 3 || count == 4) {
    for (uint_t i = 0; i < 3; i++) {
      const Vertex& c = shape.GetPoint(i);
      const ENGINE::Vector2<float_type> tC = shape.GetTransformedPoint(i);

      GPUvert v;
      v.x = tC.x - view.GetTranslation().x;
      v.y = tC.y - view.GetTranslation().y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().Red;
      v.g = c.GetColor().Green;
      v.b = c.GetColor().Blue;
      v.a = c.GetColor().Alpha;

      _coords.push_back(v);
    }

    if (count == 3) return;
  }

  if (count == 4) {
    for (int i : {2, 3, 0}) {
      const Vertex& c = shape.GetPoint(i);
      const ENGINE::Vector2<float_type> tC = shape.GetTransformedPoint(i);

      GPUvert v;
      v.x = tC.x - view.GetTranslation().x;
      v.y = tC.y - view.GetTranslation().y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().Red;
      v.g = c.GetColor().Green;
      v.b = c.GetColor().Blue;
      v.a = c.GetColor().Alpha;

      _coords.push_back(v);
    }

    return;
  }

  for (uint_t i = 0; i < count; i++) {
    Vertex c = shape.GetPoint(i);
    ENGINE::Vector2<float_t> tC = shape.GetTransformedPoint(0);

    GPUvert v;
    v.x = tC.x + view.GetTranslation().x;
    v.y = tC.y + view.GetTranslation().y;
    v.textureX = c.GetTexturePosition().x;
    v.textureY = c.GetTexturePosition().y;
    v.r = c.GetColor().Red;
    v.g = c.GetColor().Green;
    v.b = c.GetColor().Blue;
    v.a = c.GetColor().Alpha;

    _coords.push_back(v);

    shape.GetPoint(i);
    tC = shape.GetTransformedPoint(i);

    v.x = tC.x + view.GetTranslation().x;
    v.y = tC.y + view.GetTranslation().y;
    v.textureX = c.GetTexturePosition().x;
    v.textureY = c.GetTexturePosition().y;
    v.r = c.GetColor().Red;
    v.g = c.GetColor().Green;
    v.b = c.GetColor().Blue;
    v.a = c.GetColor().Alpha;

    _coords.push_back(v);

    if (i != count) {
      shape.GetPoint(i + 1);
      tC = shape.GetTransformedPoint(i + 1);

      v.x = tC.x + view.GetTranslation().x;
      v.y = tC.y + view.GetTranslation().y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().Red;
      v.g = c.GetColor().Green;
      v.b = c.GetColor().Blue;
      v.a = c.GetColor().Alpha;

      _coords.push_back(v);
    } else {
      shape.GetPoint(i - 1);
      tC = shape.GetTransformedPoint(i - 1);

      v.x = tC.x + view.GetTranslation().x;
      v.y = tC.y + view.GetTranslation().y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().Red;
      v.g = c.GetColor().Green;
      v.b = c.GetColor().Blue;
      v.a = c.GetColor().Alpha;

      _coords.push_back(v);
    }
  }
}

void BatchRenderer::MapData() {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _coords.size() * sizeof(GPUvert), (const GLvoid *)&_coords[0]);
}

void BatchRenderer::Draw() {
  if (_blur) {
    glViewport(0, 0, 240, 135);

    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer[0]);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager::GetShader("default").Use();
    ResourceManager::GetShader("default").SetVector2f("textureSize", 8192, 8192);
    ResourceManager::GetShader("default").SetVector2f("outTextureSize", 1920, 1080);

    glBindVertexArray(_vao[0]);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetAtlas("test").Bind();
    glDrawArrays(GL_TRIANGLES, 0, _coordSplit);
    glBindVertexArray(0);

    ////////////////////

    for (uint_t i = 0; i < 2; i++) {
      glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer[(i % 2 == 0)]);
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ResourceManager::GetShader("blur").Use();
      ResourceManager::GetShader("blur").SetVector2f("textureSize", 240, 135);
      ResourceManager::GetShader("blur").SetVector2f("outTextureSize", 240, 135);
      ResourceManager::GetShader("blur").SetVector2f("direction", (i % 2 == 0), (i % 2 != 0));

      glBindVertexArray(_vao[1]);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, _renderTexture[(i % 2 != 0)]);
      glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    /////////////////////

    glViewport(0, 0, Game::GetWindowSize().x, Game::GetWindowSize().y);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager::GetShader("scale").Use();
    ResourceManager::GetShader("scale").SetVector2f("textureSize", 240, 135);
    ResourceManager::GetShader("scale").SetVector2f("outTextureSize", 1920, 1080);

    glBindVertexArray(_vao[1]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _renderTexture[0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //////////////////////////

    ResourceManager::GetShader("default").Use();
    ResourceManager::GetShader("default").SetVector2f("textureSize", 8192, 8192);
    ResourceManager::GetShader("default").SetVector2f("outTextureSize", 1920, 1080);

    glBindVertexArray(_vao[0]);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetAtlas("test").Bind();
    glDrawArrays(GL_TRIANGLES, _coordSplit, _coords.size() - _coordSplit);
    glBindVertexArray(0);
  } else {
    glViewport(0, 0, Game::GetWindowSize().x, Game::GetWindowSize().y);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int horPadding = 500;
    int vertPadding = 200;
    auto insts = ResourceManager::GetCurrentLevel()->GetInstancesFollowing();
    ENGINE::Vector2<float_t> center;
    float min_x = std::numeric_limits<float>::infinity();
    float max_x = -std::numeric_limits<float>::infinity();
    float min_y = std::numeric_limits<float>::infinity();
    float max_y = -std::numeric_limits<float>::infinity();
    for (const Instance i : insts) {
      auto& mask = i->GetMask();
      if (mask.Left < min_x) min_x = mask.Left - horPadding;
      if (mask.Right > max_x) max_x = mask.Right + horPadding;
      if (mask.Top < min_y) min_y = mask.Top - vertPadding;
      if (mask.Bottom > max_y) max_y = mask.Bottom + vertPadding;
      center += i->GetTranslation();
      center += ENGINE::Vector2<float_t>((mask.Right - mask.Left)/2, (mask.Bottom - mask.Top)/2);
    }
    center /= insts.size();
    
    float xdist = max_x - min_x;
    float ydist = max_y - min_y;
    float width, height;
    
    if (xdist/ydist < 16/9.f) {
      height = ydist;
      width = height * (16/9.f);
    }  else {
      width = xdist;
      height = width / (16/9.f);
    }

    _cameraPos -= ENGINE::Vector2<float_t>(_cameraPos.x - center.x, _cameraPos.y - center.y) * 0.02;
    _idealRes -= ENGINE::Vector2<float_t>(_idealRes.x - width, _idealRes.y - height) * 0.03;
    
    ENGINE::Vector2<float_t> halfRes = _idealRes/2.f;
    
    ResourceManager::GetShader("default").Use();
    ResourceManager::GetShader("default").SetVector2f("textureSize", 8192, 8192);
    ResourceManager::GetShader("default").SetVector2f("outTextureSize", 1920, 1080);
    glm::mat4 projection = glm::ortho(_cameraPos.x - halfRes.x, _cameraPos.x + halfRes.x, _cameraPos.y + halfRes.y, _cameraPos.y - halfRes.y, -1.0f, 1.0f); 
    ResourceManager::GetShader("default").SetMatrix4("projection", projection);

    glBindVertexArray(_vao[0]);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetAtlas("test").Bind();
    glDrawArrays(GL_TRIANGLES, 0, _coords.size());
    glBindVertexArray(0);
  }
}

void BatchRenderer::Clear() { _coords.clear(); }

void BatchRenderer::initRenderData() {
  vert[0].x = 0;
  vert[0].y = 0;
  vert[0].textureX = 0;
  vert[0].textureY = 1;

  vert[1].x = 1;
  vert[1].y = 0;
  vert[1].textureX = 1;
  vert[1].textureY = 1;

  vert[2].x = 1;
  vert[2].y = 1;
  vert[2].textureX = 1;
  vert[2].textureY = 0;

  vert[3].x = 0;
  vert[3].y = 0;
  vert[3].textureX = 0;
  vert[3].textureY = 1;

  vert[4].x = 0;
  vert[4].y = 1;
  vert[4].textureX = 0;
  vert[4].textureY = 0;

  vert[5].x = 1;
  vert[5].y = 1;
  vert[5].textureX = 1;
  vert[5].textureY = 0;

  for (uint_t i = 0; i < 2; i++) {
    glGenVertexArrays(1, &_vao[i]);
    glGenBuffers(1, &_vbo[i]);

    if (i == 0) {
      glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GPUvert) * 3000, nullptr, GL_STREAM_DRAW);
    } else {
      glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GPUvert) * 6, &vert, GL_STATIC_DRAW);
    }

    glBindVertexArray(_vao[i]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_SHORT, GL_FALSE, sizeof(GPUvert), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GPUvert), (GLvoid*)offsetof(GPUvert, r));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  
  #ifndef __ANDROID__
  for (uint_t i = 0; i < 2; i++) {
    glGenFramebuffers(1, &_framebuffer[i]);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer[i]);
    glGenTextures(1, &_renderTexture[i]);
    glBindTexture(GL_TEXTURE_2D, _renderTexture[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 240, 135, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  GL_TEXTURE_2D, _renderTexture[i], 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      PrintMessage("ERROR::FRAMEBUFFER: frame buffer is NOT ok!");
  }
  #endif
}

void BatchRenderer::SetCoordSplit() { _coordSplit = _coords.size(); }

void BatchRenderer::SetBlur(const bool_t& _blur) { this->_blur = _blur; }
