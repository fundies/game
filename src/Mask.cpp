#include "Mask.hpp"
#include "Logger.hpp"

#include <sstream>
#include <iostream>

Mask::Mask() {}

Mask::Mask(const Mask& mask) {
  _transform.SetTranslation(mask.GetTranslation());
  _transform.SetRotation(mask.GetRotation());
  _transform.SetScale(mask.GetScale());
  _transform.SetPivot(mask.GetPivot());
  IsCircle = mask.IsCircle;
  _shape = std::shared_ptr<Crash2D::Shape>(mask.GetShape()->Clone());
  Transform();
}

bool Mask::LoadXML(const char* xmlFile) {
  try {
    XMLParser parser;

    if (!parser.Open(xmlFile)) return false;

    auto typeElement = parser.Root->Child.begin();
    std::string type = typeElement->first;

    if (type == "polyline") {
      std::string pointsStr = typeElement->second[0]->Attr.at("points")->GetString();

      std::istringstream ss(pointsStr);
      std::string token;

      std::vector<Crash2D::Vector2> points;

      while (std::getline(ss, token, ' ')) {
        float x, y;
        std::istringstream iss(token);

        if (iss >> x && iss.get() && iss >> y) {
          points.push_back(Crash2D::Vector2(x, y));
        }

        _shape = std::shared_ptr<Crash2D::Polygon>(new Crash2D::Polygon());
        _shape->SetPointCount(points.size() - 1);

        for (unsigned point = 0; point < points.size() - 1; point++) {
          _shape->SetPoint(point, points[point]);
        }

        _shape->ReCalc();
      }
    } else if (type == "circle") {
      float cx, cy, radius;
      cx = typeElement->second[0]->Attr.at("cx")->GetUnsigned();
      cy = typeElement->second[0]->Attr.at("cy")->GetUnsigned();
      radius = typeElement->second[0]->Attr.at("r")->GetUnsigned();
      _shape = std::shared_ptr<Crash2D::Circle>(new Crash2D::Circle(Crash2D::Vector2(cx, cy), radius));
      IsCircle = true;
      _shape->ReCalc();
    }

  } catch (std::exception e) {
    PrintMessage("ERROR::MASK: Failed to read: %s", xmlFile);
    return false;
  }

  return true;
}

const std::shared_ptr<Crash2D::Shape>& Mask::GetShape() const { return _shape; }

void Mask::SetTranslation(const Vec2f& t) {
  if (_shape != nullptr) {
    Transformable::SetTranslation(t);

    //Crash2D::Transformation transform;
    transform.SetTranslation(Crash2D::Vector2(t.x, t.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetRotation(const float r) {
  if (_shape != nullptr) {
    Transformable::SetRotation(r);

    //Crash2D::Transformation transform;
    transform.SetRotation(r);

    //_shape->Transform(transform);
  }
}

void Mask::Translate(const Vec2f& t) {
  if (_shape != nullptr) {
    Transformable::Translate(t);

    //Crash2D::Transformation transform;
    transform.Translate(Crash2D::Vector2(t.x, t.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetScale(const Vec2f& s) {
  if (_shape != nullptr) {
    Transformable::SetScale(s);

    //Crash2D::Transformation transform;
    transform.SetScale(Crash2D::Vector2(s.x, s.y));

    //_shape->Transform(transform);
  }
}

void Mask::SetPivot(const Vec2f& p) {
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
  
  if (_shape->IsCircle) {
    Top = _shape->GetCenter().y - _shape->GetRadius();
    Bottom = _shape->GetCenter().y + _shape->GetRadius();
    Left = _shape->GetCenter().x - _shape->GetRadius();
    Right = _shape->GetCenter().x + _shape->GetRadius();
  } else {
    for (auto p : _shape->GetPoints()) {
      if (p.y < Top) Top = p.y;

      if (p.y > Bottom) Bottom = p.y;

      if (p.x > Right) Right = p.x;

      if (p.x < Left) Left = p.x;
    }
  }
}

const Crash2D::Collision Mask::GetCollision(const Mask& mask, Vec2f aV,
                                            Vec2f bV) const {
  if (GetShape() != nullptr && mask.GetShape() != nullptr) {
    return GetShape()->GetCollision(*mask.GetShape().get());
  }

  return Crash2D::Collision();
}
