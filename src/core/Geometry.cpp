#include "Geometry.h"

Geometry::Geometry(Type type)
    : type_(type)
{
    id_ = QString("geom_%1").arg(static_cast<int>(type_));
}

Geometry::Type Geometry::type() const {
    return type_;
}

void Geometry::setType(Type type) {
    type_ = type;
}

QString Geometry::id() const {
    return id_;
}

void Geometry::setId(const QString& id) {
    id_ = id;
}

QString Geometry::layerName() const {
    return layer_name_;
}

void Geometry::setLayerName(const QString& layerName) {
    layer_name_ = layerName;
}

QColor Geometry::color() const {
    return color_;
}

void Geometry::setColor(const QColor& color) {
    color_ = color;
}

double Geometry::lineWeight() const {
    return line_weight_;
}

void Geometry::setLineWeight(double weight) {
    line_weight_ = weight;
}
