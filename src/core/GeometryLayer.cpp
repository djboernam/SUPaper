#include "GeometryLayer.h"

#include <algorithm>

GeometryShape::GeometryShape(Type type) : type_(type) {
    id_ = QString("shape_%1").arg(static_cast<int>(type));
}

Line::Line(QVector2D start, QVector2D end)
    : GeometryShape(Type::Line), start_(start), end_(end) {}

Rectangle::Rectangle(QVector2D topLeft, double width, double height)
    : GeometryShape(Type::Rectangle), top_left_(topLeft), width_(width), height_(height) {}

Circle::Circle(QVector2D center, double radius)
    : GeometryShape(Type::Circle), center_(center), radius_(radius) {}

TextShape::TextShape(const QString& text, QVector2D position)
    : GeometryShape(Type::Text), text_(text), position_(position) {}

GeometryLayer::GeometryLayer(const QString& name) : name_(name) {}

void GeometryLayer::addShape(std::shared_ptr<GeometryShape> shape) {
    shapes_.push_back(shape);
}

bool GeometryLayer::removeShape(std::shared_ptr<GeometryShape> shape) {
    auto it = std::find(shapes_.begin(), shapes_.end(), shape);
    if (it != shapes_.end()) {
        shapes_.erase(it);
        return true;
    }
    return false;
}

void GeometryLayer::clear() {
    shapes_.clear();
}
