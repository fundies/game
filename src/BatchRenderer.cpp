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

BatchRenderer::BatchRenderer() : _blur(false), _cameraMode(CAMERAMODE::CAMERA_SINGLE), _targetRes(1920,1080) { initRenderData(); }

BatchRenderer::~BatchRenderer() {
  glDeleteVertexArrays(1, &_vao[0]);
  glDeleteVertexArrays(1, &_vao[1]);
}

void BatchRenderer::DrawSprite(const Sprite& spr) { DrawConvexShape(spr); }

void BatchRenderer::DrawText(const Text& text, Color color) {
  for (const auto& letter : text.GetLetters()) {
    if (text.GetShadowPosition() != Vec2f(0, 0)) {
      Sprite t = letter;
      t.SetScale(letter.GetScale() * text.GetScale());
      t.SetRotation(letter.GetRotation() + text.GetRotation());
      t.SetTranslation(letter.GetTranslation() + text.GetTranslation() + text.GetShadowPosition());
      t.SetColor(text.GetShadowColor());

      DrawSprite(t);
    }

    Sprite t = letter;
    t.SetScale(letter.GetScale() * text.GetScale());
    t.SetRotation(letter.GetRotation() + text.GetRotation());
    t.SetTranslation(letter.GetTranslation() + text.GetTranslation());

    DrawSprite(t);
  }
}

void BatchRenderer::DrawLine(Vec2f a, Vec2f b, Color color) {
  ConvexShape line(4);
  line.SetPointPosition(0, a);
  line.SetPointPosition(1, b);
  line.SetPointPosition(2, b + Vec2f(0, 4));
  line.SetPointPosition(3, a + Vec2f(0, 4));
  
  for (size_t i = 0; i < 4; ++i)
    line.SetColor(color);
  
  DrawConvexShape(line);
}

void BatchRenderer::DrawCircle(Vec2f pos, float radius, Color color, size_t pointCount) {
  ConvexShape circle(pointCount);
  for (size_t i = 0; i < pointCount; i++) {
    float angle = ((2 * M_PI) / pointCount) * (i+1);
    circle.SetPointPosition(i, pos + Vec2f(radius * std::cos(angle), radius * -std::sin(angle)));
    circle.SetColor(color);
  }
  
  circle.CalcCenter();
  
  DrawConvexShape(circle);
}

void BatchRenderer::PushVert(const GPUvert& v) {
  // Add Vertex to vertex buffer if unique and store position in index buffer
  auto it = std::find(std::begin(_coords), std::end(_coords), v);
  if (it == _coords.end()) {
    _coords.push_back(v);
    _indexBuffer.push_back(_coords.size() - 1);
  } else {
    _indexBuffer.push_back(std::distance(_coords.begin(), it));
  }
}

void BatchRenderer::DrawConvexShape(const ConvexShape& shape, Color color) {
  ConvexShape copy = shape;
  copy.SetColor(color);
  DrawConvexShape(copy);
}

void BatchRenderer::DrawConvexShape(const ConvexShape& shape) {
  unsigned count = shape.GetPointCount();

  if (count < 3) return;

  if (count == 3 || count == 4) {
    for (unsigned i = 0; i < 3; i++) {
      const Vertex& c = shape.GetPoint(i);
      const Vec2f tC = shape.GetTransformedPoint(i);

      GPUvert v;
      v.x = tC.x;
      v.y = tC.y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().RedVal;
      v.g = c.GetColor().GreenVal;
      v.b = c.GetColor().BlueVal;
      v.a = c.GetColor().AlphaVal;

      PushVert(v);
      
    }

    if (count == 3) return;
  }

  if (count == 4) {
    for (int i : {2, 3, 0}) {
      const Vertex& c = shape.GetPoint(i);
      const Vec2f tC = shape.GetTransformedPoint(i);

      GPUvert v;
      v.x = tC.x;
      v.y = tC.y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().RedVal;
      v.g = c.GetColor().GreenVal;
      v.b = c.GetColor().BlueVal;
      v.a = c.GetColor().AlphaVal;

      PushVert(v);
    }

    return;
  }

  for (unsigned i = 0; i < count; i++) {
    Vertex c = shape.GetPoint(i);
    Vec2f tC = shape.GetTransformedPoint(0);

    GPUvert v;
    v.x = tC.x;
    v.y = tC.y;
    v.textureX;
    v.textureY;
    v.r = c.GetColor().RedVal;
    v.g = c.GetColor().GreenVal;
    v.b = c.GetColor().BlueVal;
    v.a = c.GetColor().AlphaVal;

    PushVert(v);

    shape.GetPoint(i);
    tC = shape.GetTransformedPoint(i);

    v.x = tC.x;
    v.y = tC.y;
    v.textureX;
    v.textureY;
    v.r = c.GetColor().RedVal;
    v.g = c.GetColor().GreenVal;
    v.b = c.GetColor().BlueVal;
    v.a = c.GetColor().AlphaVal;

    PushVert(v);

    if (i != count-1) {
      shape.GetPoint(i + 1);
      tC = shape.GetTransformedPoint(i + 1);

      v.x = tC.x;
      v.y = tC.y;
      v.textureX;
      v.textureY;
      v.r = c.GetColor().RedVal;
      v.g = c.GetColor().GreenVal;
      v.b = c.GetColor().BlueVal;
      v.a = c.GetColor().AlphaVal;

      PushVert(v);
    } else {
      shape.GetPoint(i - 1);
      tC = shape.GetTransformedPoint(i - 1);

      v.x = tC.x;
      v.y = tC.y;
      v.textureX = c.GetTexturePosition().x;
      v.textureY = c.GetTexturePosition().y;
      v.r = c.GetColor().RedVal;
      v.g = c.GetColor().GreenVal;
      v.b = c.GetColor().BlueVal;
      v.a = c.GetColor().AlphaVal;

      PushVert(v);
    }
  }
}

void BatchRenderer::MapData() {
  // Push Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _coords.size() * sizeof(GPUvert), (const GLvoid *)&_coords[0]);
  
  // Push Index Buffer
  glGenBuffers(1, &elementbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer.size() * sizeof(unsigned int), &_indexBuffer[0], GL_STATIC_DRAW);
}

glm::mat4 BatchRenderer::GetProjection() {
  // Players we want in view
  auto insts = ResourceManager::GetCurrentLevel()->GetInstancesFollowing();
  
  // Zoom in/out on rectangle containing all players
  if (_cameraMode == CAMERA_GROUP) {  
    Vec2f center;
    float min_x = std::numeric_limits<float>::infinity();
    float max_x = -std::numeric_limits<float>::infinity();
    float min_y = std::numeric_limits<float>::infinity();
    float max_y = -std::numeric_limits<float>::infinity();
    for (const Instance i : insts) {
      auto& mask = i->GetMask(0);
      if (mask.Left < min_x) min_x = mask.Left - _cameraHorPadding;
      if (mask.Right > max_x) max_x = mask.Right + _cameraHorPadding;
      if (mask.Top < min_y) min_y = mask.Top - _cameraVertPadding;
      if (mask.Bottom > max_y) max_y = mask.Bottom + _cameraVertPadding;
      center += i->GetTranslation();
      center += Vec2f((mask.Right - mask.Left)/2, (mask.Bottom - mask.Top)/2);
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

    _cameraPos -= Vec2f(_cameraPos.x - center.x, _cameraPos.y - center.y) * _panSpeed;
    _cameraPos.x = static_cast<int>(_cameraPos.x);
    _cameraPos.y = static_cast<int>(_cameraPos.y);
    
    _targetRes -= Vec2f(_targetRes.x - width, _targetRes.y - height) * _zoomSpeed;
    
    Vec2f halfRes(static_cast<int>(_targetRes.x/2.f), static_cast<int>(_targetRes.y/2.f));
    return glm::ortho(_cameraPos.x - halfRes.x, _cameraPos.x + halfRes.x, _cameraPos.y + halfRes.y, _cameraPos.y - halfRes.y, -1.0f, 1.0f);
  } else {
    // Put player at center
    Vec2f halfRes(1920/2.f, 1080/2.f);
    _cameraPos =  insts[0]->GetTranslation();
    return glm::ortho(_cameraPos.x - halfRes.x, _cameraPos.x + halfRes.x, _cameraPos.y + halfRes.y, _cameraPos.y - halfRes.y, -1.0f, 1.0f);
  }
}

void BatchRenderer::Draw() {
  // We draw to render texture first
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  glViewport(0, 0, 1920, 1080);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Update our camera zoom / position
  ResourceManager::GetShader("default").Use();
  ResourceManager::GetShader("default").SetVector2f("textureSize", 8192, 8192);
  ResourceManager::GetShader("default").SetVector2f("outTextureSize", 1920, 1080);
  ResourceManager::GetShader("default").SetMatrix4("projection", GetProjection());

  glBindVertexArray(_vao[0]);
  glActiveTexture(GL_TEXTURE0);
  ResourceManager::GetAtlas("test").Bind();
    
  // Index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

  // Draw the triangles
  glDrawElements(
     GL_TRIANGLES,        // mode
     _indexBuffer.size(), // count
     GL_UNSIGNED_INT,     // type
     (void*)0             // element array buffer offset
  );

  // Unbind vao
  glBindVertexArray(0);

  // Draw the render texture to the screen
  ResourceManager::GetShader("scale").Use();
  ResourceManager::GetShader("scale").SetVector2f("outTextureSize", 1920, 1080);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
  glViewport(0, 0, Game::GetWindowSize().x, Game::GetWindowSize().y);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(_vao[1]);
  glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  glDrawArrays(GL_TRIANGLES, 0, 6);  
}

void BatchRenderer::Clear() { _coords.clear(); _indexBuffer.clear(); }

void BatchRenderer::initRenderData() {
  // Note render texture is upside down so we need to flip it
  vert[0].x = 0;
  vert[0].y = 0;
  vert[0].textureX = 0;
  vert[0].textureY = 1080;

  vert[1].x = 1;
  vert[1].y = 0;
  vert[1].textureX = 1920;
  vert[1].textureY = 1080;

  vert[2].x = 1;
  vert[2].y = 1;
  vert[2].textureX = 1920;
  vert[2].textureY = 0;

  vert[3].x = 0;
  vert[3].y = 0;
  vert[3].textureX = 0;
  vert[3].textureY = 1080;

  vert[4].x = 0;
  vert[4].y = 1;
  vert[4].textureX = 0;
  vert[4].textureY = 0;

  vert[5].x = 1;
  vert[5].y = 1;
  vert[5].textureX = 1920;
  vert[5].textureY = 0;
  
  for (unsigned i = 0; i < 2; i++) {
    glGenVertexArrays(1, &_vao[i]);
    glGenBuffers(1, &_vbo[i]);

    if (i == 0) {
      glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
      // FIXME: this should be based on instance count not hardcoded
      glBufferData(GL_ARRAY_BUFFER, sizeof(GPUvert) * 3000, nullptr, GL_STREAM_DRAW);
    } else {
      glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GPUvert) * 6, &vert, GL_STATIC_DRAW);
    }

    glBindVertexArray(_vao[i]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_INT, GL_FALSE, sizeof(GPUvert), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GPUvert), (GLvoid*)offsetof(GPUvert, r));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  
  // Create a color attachment texture
  glGenTextures(1, &textureColorbuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
  
  // Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
  
  // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BatchRenderer::SetCoordSplit() { _coordSplit = _coords.size(); }

void BatchRenderer::SetBlur(const bool& _blur) { this->_blur = _blur; }
