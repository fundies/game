#ifndef SHADER_H
#define SHADER_H

#include "Types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
 public:
  Shader() {}
  bool LoadShaderFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);

  Shader& Use();
  void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
  void SetFloat(const char* name, float value, bool useShader = false);
  void SetInteger(const char* name, int value, bool useShader = false);
  void SetVector2f(const char* name, float x, float y, bool useShader = false);
  void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
  void SetVector4f(const char* name, float x, float y, float z, float w,
                   bool useShader = false);
  void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
  const unsigned& GetID() const;

 protected:
  void checkCompileErrors(unsigned object, std::string type);
  unsigned _ID;
};

#endif
