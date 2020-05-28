#include "Shader.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

#include <fstream>
#include <sstream>

Shader &Shader::Use() {
  glUseProgram(this->_ID);
  return *this;
}

bool Shader::LoadShaderFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {

  const char *vShaderCode = FileRead(vShaderFile);
  const char *fShaderCode = FileRead(fShaderFile);
  const char *gShaderCode = FileRead(gShaderFile);

  Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

  return true;
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
  unsigned sVertex, sFragment, gShader = 0;

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
  // Delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);

  if (geometrySource != nullptr) glDeleteShader(gShader);
}

void Shader::SetFloat(const char *name, float value, bool useShader) {
  if (useShader) this->Use();

  glUniform1f(glGetUniformLocation(this->_ID, name), value);
}

void Shader::SetInteger(const char *name, int value, bool useShader) {
  if (useShader) this->Use();

  glUniform1i(glGetUniformLocation(this->_ID, name), value);
}

void Shader::SetVector2f(const char *name, float x, float y, bool useShader) {
  if (useShader) this->Use();

  glUniform2f(glGetUniformLocation(this->_ID, name), x, y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader) {
  if (useShader) this->Use();

  glUniform3f(glGetUniformLocation(this->_ID, name), x, y, z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader) {
  if (useShader) this->Use();

  glUniform4f(glGetUniformLocation(this->_ID, name), x, y, z, w);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned object, std::string type) {
  int success;
  char infoLog[1024];

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

const unsigned &Shader::GetID() const { return _ID; }
