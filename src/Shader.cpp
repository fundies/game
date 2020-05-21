#include "Shader.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

#include <fstream>
#include <sstream>

Shader &Shader::Use() {
  glUseProgram(this->_ID);
  return *this;
}

bool_t Shader::LoadShaderFile(const char_t *vShaderFile, const char_t *fShaderFile, const char_t *gShaderFile) {

  const char_t *vShaderCode = FileRead(vShaderFile);
  const char_t *fShaderCode = FileRead(fShaderFile);
  const char_t *gShaderCode = FileRead(gShaderFile);

  Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

  return true;
}

void Shader::Compile(const char_t *vertexSource, const char_t *fragmentSource, const char_t *geometrySource) {
  uint_t sVertex, sFragment, gShader = 0;

  // Vertex Shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, nullptr);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");
  // Fragment Shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, nullptr);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");

  // If geometry shader source code is given, also compile geometry shader
  if (geometrySource != nullptr) {
    /*gShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gShader, 1, &geometrySource, nullptr);
    glCompileShader(gShader);
    checkCompileErrors(gShader, "GEOMETRY");*/
  }

  // Shader Program
  this->_ID = glCreateProgram();
  glAttachShader(this->_ID, sVertex);
  glAttachShader(this->_ID, sFragment);

  if (geometrySource != nullptr) glAttachShader(this->_ID, gShader);

  glLinkProgram(this->_ID);
  checkCompileErrors(this->_ID, "PROGRAM");
  // Delete the shaders as they're linked int_to our program now and no longer necessery
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);

  if (geometrySource != nullptr) glDeleteShader(gShader);
}

void Shader::SetFloat(const char_t *name, float_type value, bool_t useShader) {
  if (useShader) this->Use();

  glUniform1f(glGetUniformLocation(this->_ID, name), value);
}

void Shader::SetInteger(const char_t *name, int_t value, bool_t useShader) {
  if (useShader) this->Use();

  glUniform1i(glGetUniformLocation(this->_ID, name), value);
}

void Shader::SetVector2f(const char_t *name, float_type x, float_type y, bool_t useShader) {
  if (useShader) this->Use();

  glUniform2f(glGetUniformLocation(this->_ID, name), x, y);
}

void Shader::SetVector3f(const char_t *name, float_type x, float_type y, float_type z, bool_t useShader) {
  if (useShader) this->Use();

  glUniform3f(glGetUniformLocation(this->_ID, name), x, y, z);
}

void Shader::SetVector4f(const char_t *name, float_type x, float_type y, float_type z, float_type w, bool_t useShader) {
  if (useShader) this->Use();

  glUniform4f(glGetUniformLocation(this->_ID, name), x, y, z, w);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(uint_t object, string_t type) {
  int_t success;
  char_t infoLog[1024];

  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(object, 1024, nullptr, infoLog);
      PrintMessage("ERROR::SHADER: Compile-time error: Type: %s \n %s \n -- --------------------------------------------------- -- ", type.c_str(), infoLog);
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);

    if (!success) {
		glGetShaderInfoLog(object, 1024, nullptr, infoLog);
		PrintMessage("ERROR::SHADER: Link-time error: Type: %s \n %s \n -- --------------------------------------------------- -- ", type.c_str(), infoLog);
    }
  }
}

const uint_t &Shader::GetID() const { return _ID; }
