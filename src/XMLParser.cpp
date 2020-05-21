#include "XMLParser.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

float_type XMLAttrBase::GetFloat() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"float\"");
  throw std::runtime_error("Invalid attribute type");
}

uint_t XMLAttrBase::GetUnsigned() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"unsigned\"");
  throw std::runtime_error("Invalid attribute type");
}

int_t XMLAttrBase::GetInt() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"int\"");
  throw std::runtime_error("Invalid attribute type");
}

string_t XMLAttrBase::GetString() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"string\"");
  throw std::runtime_error("Invalid attribute type");
}

XMLTag::XMLTag(string_t name) : _name(name) {}

void XMLTag::AddChild(tagPtr child) {
  if (Child.find(child->_name) == std::end(Child))
    Child.emplace(child->_name, vector_t<tagPtr>{child});
  else
    Child.at(child->_name).push_back(child);
}

bool_t XMLParser::Open(const char_t* fileName) {
  doc.Parse(FileRead(fileName));

  if (doc.ErrorID() == 0) {
    Parse();
    return true;
  }

  doc.PrintError();

  return false;
}

void XMLParser::Parse() {
  tinyxml2::XMLElement* root = doc.RootElement();
  Root = tagPtr(new XMLTag(root->Name()));

  recParse(root, Root);
}

void XMLParser::recParse(const tinyxml2::XMLElement* element, tagPtr parentTag) {
  for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
    string_t attrName = attr->Name();
    string_t attrValStr = attr->Value();
    Type attrType = getType(attrValStr);
    attrPtr attrValue;

    switch (attrType) {
      case Type::STRING: {
        attrValue = attrPtr(new XMLAttr<string_t>(attr->Value()));
        break;
      }

      case Type::FLOAT: {
        attrValue = attrPtr(new XMLAttr<float_type>(attr->FloatValue()));
        break;
      }

      case Type::INT: {
        attrValue = attrPtr(new XMLAttr<int_t>(attr->IntValue()));
        break;
      }

      case Type::UNSIGNED: {
        attrValue = attrPtr(new XMLAttr<uint_t>(attr->UnsignedValue()));
        break;
      }
    }

    parentTag->Attr.emplace(attrName, attrValue);
  }

  for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr;
       child = child->NextSiblingElement()) {
    tagPtr childTag(new XMLTag(child->Name()));
    parentTag->AddChild(childTag);
    recParse(child, childTag);
  }
}

Type XMLParser::getType(string_t str) {
  bool_t hasSign = false;
  bool_t hasDec = false;
  bool_t hasAlpha = (str.find_first_of("ABCDEFGHIJKLMNOPQRTSUVWXYZabcdefghijklmnopqrstuvwxyz,") != string_t::npos);

  if (hasAlpha) return Type::STRING;

  for (char_t c : str) {
    if (c == '-') hasSign = true;

    if (c == '.') hasDec = true;
  }

  if (hasDec)
    return Type::FLOAT;
  else if (hasSign)
    return Type::INT;
  else
    return Type::UNSIGNED;
}
