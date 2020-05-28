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

class Object;
using Instance = std::shared_ptr<Object>;

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif
