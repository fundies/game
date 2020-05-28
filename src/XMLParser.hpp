#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "Types.hpp"

#include <tinyxml2.h>

typedef enum class Type : int { FLOAT = 0, UNSIGNED = 1, INT = 2, STRING = 3 } Type;

class XMLAttrBase {
 public:
  virtual float GetFloat();
  virtual unsigned GetUnsigned();
  virtual int GetInt();
  virtual std::string GetString();
};

template <typename T>
class XMLAttr;

template <>
class XMLAttr<float> : public XMLAttrBase {
 public:
  XMLAttr(float value) : _value(value) {}
  float GetFloat() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  float _value;
};

template <>
class XMLAttr<unsigned> : public XMLAttrBase {
 public:
  XMLAttr(unsigned value) : _value(value) {}
  unsigned GetUnsigned() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  unsigned _value;
};

template <>
class XMLAttr<int> : public XMLAttrBase {
 public:
  XMLAttr(int value) : _value(value) {}
  int GetInt() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  int _value;
};

template <>
class XMLAttr<std::string> : public XMLAttrBase {
 public:
  XMLAttr(std::string value) : _value(value) {}
  std::string GetString() override { return _value; }
  virtual ~XMLAttr() {};

 private:
  std::string _value;
};

using attrPtr = std::shared_ptr<XMLAttrBase>;

class XMLTag;
using tagPtr = std::shared_ptr<XMLTag>;

class XMLTag {
 public:
  XMLTag(std::string name);
  void AddChild(tagPtr child);

  std::string _name;
  std::map<std::string, attrPtr> Attr;
  std::map<std::string, std::vector<tagPtr>> Child;
};

class XMLParser {
 public:
  bool Open(const char* fileName);
  void Parse();

  tagPtr Root;

 private:
  void recParse(const tinyxml2::XMLElement* element, tagPtr parentTag);
  Type getType(std::string str);

 private:
  tinyxml2::XMLDocument doc;
};

#endif
