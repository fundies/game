#ifndef TYPES_HPP
#define TYPES_HPP

#include <glad/glad.h>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

using float_type = GLfloat;
using int_t = GLint;
using uint_t = GLuint;
using char_t = GLchar;
using ubyte_t = GLubyte;
using bool_t = GLboolean;
using string_t = std::string;
using uchar_t = unsigned char;
using short_t = GLshort;

template <class T>
using vector_t = std::vector<T>;

template <class T, class V>
using map_t = std::map<T, V>;

template <class T, class V>
using umap_t = std::unordered_map<T, V>;

template <class T>
using shared_ptr_t = std::shared_ptr<T>;

class Object;
using Instance = shared_ptr_t<Object>;

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif
