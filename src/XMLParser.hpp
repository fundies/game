#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "Types.hpp"

#include <tinyxml2.h>

typedef enum class Type : int_t { FLOAT = 0, UNSIGNED = 1, INT = 2, STRING = 3 } Type;

class XMLAttrBase {
 public:
  virtual float_type GetFloat();
  virtual uint_t GetUnsigned();
  virtual int_t GetInt();
  virtual string_t GetString();
};

template <typename T>
class XMLAttr;

template <>
class XMLAttr<float_type> : public XMLAttrBase {
 public:
  XMLAttr(float_type value) : _value(value) {}
  float_type GetFloat() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  float_type _value;
};

template <>
class XMLAttr<uint_t> : public XMLAttrBase {
 public:
  XMLAttr(uint_t value) : _value(value) {}
  uint_t GetUnsigned() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  uint_t _value;
};

template <>
class XMLAttr<int_t> : public XMLAttrBase {
 public:
  XMLAttr(int_t value) : _value(value) {}
  int_t GetInt() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  int_t _value;
};

template <>
class XMLAttr<string_t> : public XMLAttrBase {
 public:
  XMLAttr(string_t value) : _value(value) {}
  string_t GetString() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  string_t _value;
};

using attrPtr = shared_ptr_t<XMLAttrBase>;

class XMLTag;
using tagPtr = shared_ptr_t<XMLTag>;

class XMLTag {
 public:
  XMLTag(string_t name);
  void AddChild(tagPtr child);

  string_t _name;
  map_t<string_t, attrPtr> Attr;
  map_t<string_t, vector_t<tagPtr>> Child;
};

class XMLParser {
 public:
  bool_t Open(const char_t* fileName);
  void Parse();

  tagPtr Root;

 private:
  void recParse(const tinyxml2::XMLElement* element, tagPtr parentTag);
  Type getType(string_t str);

 private:
  tinyxml2::XMLDocument doc;
};

#endif
