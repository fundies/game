#include "XMLParser.hpp"
#include "FileUtil.hpp"
#include "Logger.hpp"

float XMLAttrBase::GetFloat() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"float\"");
  throw std::runtime_error("Invalid attribute type");
}

unsigned XMLAttrBase::GetUnsigned() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"unsigned\"");
  throw std::runtime_error("Invalid attribute type");
}

int XMLAttrBase::GetInt() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"int\"");
  throw std::runtime_error("Invalid attribute type");
}

std::string XMLAttrBase::GetString() {
  PrintMessage("ERROR::XMLPARSER: Invalid attribute type \"string\"");
  throw std::runtime_error("Invalid attribute type");
}

XMLTag::XMLTag(std::string name) : _name(name) {}

void XMLTag::AddChild(tagPtr child) {
  if (Child.find(child->_name) == std::end(Child))
    Child.emplace(child->_name, std::vector<tagPtr>{child});
  else
    Child.at(child->_name).push_back(child);
}

bool XMLParser::Open(const char* fileName) {
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
    std::string attrName = attr->Name();
    std::string attrValStr = attr->Value();
    Type attrType = getType(attrValStr);
    attrPtr attrValue;

    switch (attrType) {
      case Type::STRING: {
        attrValue = attrPtr(new XMLAttr<std::string>(attr->Value()));
        break;
      }

      case Type::FLOAT: {
        attrValue = attrPtr(new XMLAttr<float>(attr->FloatValue()));
        break;
      }

      case Type::INT: {
        attrValue = attrPtr(new XMLAttr<int>(attr->IntValue()));
        break;
      }

      case Type::UNSIGNED: {
        attrValue = attrPtr(new XMLAttr<unsigned>(attr->UnsignedValue()));
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

Type XMLParser::getType(std::string str) {
  bool hasSign = false;
  bool hasDec = false;
  bool hasAlpha = (str.find_first_of("ABCDEFGHIJKLMNOPQRTSUVWXYZabcdefghijklmnopqrstuvwxyz,") != std::string::npos);

  if (hasAlpha) return Type::STRING;

  for (char c : str) {
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
