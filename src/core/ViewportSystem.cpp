#include "ViewportSystem.h"

#include <algorithm>

ViewportLayer::ViewportLayer(const QString& name) : name_(name) {}

ViewportSystem::ViewportSystem() = default;

std::shared_ptr<ViewportLayer> ViewportSystem::createViewport(const QString& name) {
    auto viewport = std::make_shared<ViewportLayer>(name);
    viewports_.push_back(viewport);
    return viewport;
}

bool ViewportSystem::deleteViewport(std::shared_ptr<ViewportLayer> viewport) {
    auto it = std::find(viewports_.begin(), viewports_.end(), viewport);
    if (it != viewports_.end()) {
        viewports_.erase(it);
        return true;
    }
    return false;
}
