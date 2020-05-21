#include "Mask.hpp"
#include "Logger.hpp"

#include <sstream>
#include <iostream>

Mask::Mask() {}

Mask::Mask(const Mask& mask) {
  SetTranslation(mask.GetTranslation());
  SetRotation(mask.GetRotation());
  SetScale(mask.GetScale());
  SetPivot(mask.GetPivot());
  _shape = std::shared_ptr<Crash2D::Shape>(mask.GetShape()->Clone());
  Transform();
}

bool_t Mask::LoadXML(const char_t* xmlFile) {
  try {
    XMLParser parser;

    if (!parser.Open(xmlFile)) return false;

    auto typeElement = parser.Root->Child.begin();
    string_t type = typeElement->first;

    if (type == "polyline") {
      string_t pointsStr = typeElement->second[0]->Attr.at("points")->GetString();

      std::istringstream ss(pointsStr);
      std::string token;

      vector_t<Crash2D::Vector2> points;

      while (std::getline(ss, token, ' ')) {
        float x, y;
        std::istringstream iss(token);

        if (iss >> x && iss.get() && iss >> y) {
          points.push_back(Crash2D::Vector2(x, y));
        }

        _shape = std::shared_ptr<Crash2D::Polygon>(new Crash2D::Polygon());
        _shape->SetPointCount(points.size() - 1);

        for (uint_t point = 0; point < points.size() - 1; point++) {
          _shape->SetPoint(point, points[point]);
        }

        _shape->ReCalc();
      }
    }

  } catch (std::exception e) {
    PrintMessage("ERROR::MASK: Failed to read: %s", xmlFile);
    return false;
  }

  return true;
}

const std::shared_ptr<Crash2D::Shape>& Mask::GetShape() const { return _shape; }

void Mask::SetTranslation(const ENGINE::Vector2<float_type>& t) {
  if (_shape != nullptr) {
    Transformable::SetTranslation(t);

    //Crash2D::Transformation transform;
    transform.SetTranslation(Crash2D::Vector2(t.x, t.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetRotation(const float_type r) {
  if (_shape != nullptr) {
    Transformable::SetRotation(r);

    //Crash2D::Transformation transform;
    transform.SetRotation(r);

    //_shape->Transform(transform);
  }
}

void Mask::Translate(const ENGINE::Vector2<float_type>& t) {
  if (_shape != nullptr) {
    Transformable::Translate(t);

    //Crash2D::Transformation transform;
    transform.Translate(Crash2D::Vector2(t.x, t.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetScale(const ENGINE::Vector2<float_type>& s) {
  if (_shape != nullptr) {
    Transformable::SetScale(s);

    //Crash2D::Transformation transform;
    transform.SetScale(Crash2D::Vector2(s.x, s.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetPivot(const ENGINE::Vector2<float_type>& p) {
  if (_shape != nullptr) {
    Transformable::SetPivot(p);

    //Crash2D::Transformation transform;
    transform.SetPivot(Crash2D::Vector2(p.x, p.y));

    //_shape->Transform(transform);
  }
}

void Mask::Transform() {
  _shape->Transform(transform);
  _shape->ReCalc();
  transform = Crash2D::Transformation();

  Top = std::numeric_limits<float>::infinity();
  Bottom = -std::numeric_limits<float>::infinity();
  Left = std::numeric_limits<float>::infinity();
  Right = -std::numeric_limits<float>::infinity();

  for (auto p : _shape->GetPoints()) {
    if (p.y < Top) Top = p.y;

    if (p.y > Bottom) Bottom = p.y;

    if (p.x > Right) Right = p.x;

    if (p.x < Left) Left = p.x;
  }
}

const Crash2D::Collision Mask::GetCollision(const Mask& mask, ENGINE::Vector2<float_type> aV,
                                            ENGINE::Vector2<float_type> bV) const {
  if (GetShape() != nullptr && mask.GetShape() != nullptr) {
    return GetShape()->GetCollision(*mask.GetShape().get());
  }

  return Crash2D::Collision();
}
