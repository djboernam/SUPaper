#include "Sheet.h"

#include "Viewport.h"

Sheet::Sheet(QString name, QString size, QString orientation)
    : name_(std::move(name)), size_(std::move(size)), orientation_(std::move(orientation))
{
}

QString Sheet::name() const {
    return name_;
}

QString Sheet::size() const {
    return size_;
}

QString Sheet::orientation() const {
    return orientation_;
}

void Sheet::addViewport(const Viewport& viewport) {
    viewports_.push_back(viewport);
}

std::vector<Viewport>& Sheet::viewports() {
    return viewports_;
}

const std::vector<Viewport>& Sheet::viewports() const {
    return viewports_;
}
