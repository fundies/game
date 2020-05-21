#ifndef SHADER_H
#define SHADER_H

#include "Types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
 public:
  Shader() {}
  bool_t LoadShaderFile(const char_t* vShaderFile, const char_t* fShaderFile, const char_t* gShaderFile);

  Shader& Use();
  void Compile(const char_t* vertexSource, const char_t* fragmentSource, const char_t* geometrySource = nullptr);
  void SetFloat(const char_t* name, float_type value, bool_t useShader = false);
  void SetInteger(const char_t* name, int_t value, bool_t useShader = false);
  void SetVector2f(const char_t* name, float_type x, float_type y, bool_t useShader = false);
  void SetVector3f(const char_t* name, float_type x, float_type y, float_type z, bool_t useShader = false);
  void SetVector4f(const char_t* name, float_type x, float_type y, float_type z, float_type w,
                   bool_t useShader = false);
  void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
  const uint_t& GetID() const;

 protected:
  void checkCompileErrors(uint_t object, string_t type);
  uint_t _ID;
};

#endif
