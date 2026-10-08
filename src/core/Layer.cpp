#include "Layer.h"

Layer::Layer(QString name, QColor color)
    : name_(std::move(name)), color_(std::move(color))
{
}

QString Layer::name() const {
    return name_;
}

void Layer::setName(const QString& name) {
    name_ = name;
}

QColor Layer::color() const {
    return color_;
}

void Layer::setColor(const QColor& color) {
    color_ = color;
}

bool Layer::visible() const {
    return visible_;
}

void Layer::setVisible(bool visible) {
    visible_ = visible;
}

bool Layer::locked() const {
    return locked_;
}

void Layer::setLocked(bool locked) {
    locked_ = locked;
}
