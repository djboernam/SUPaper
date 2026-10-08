#include "ModelViewer.h"
#include "../importers/SKPImporter.h"

#include <QMatrix4x4>
#include <QVector3D>
#include <cmath>

QMatrix4x4 Viewport3D::getProjectionMatrix(float aspectRatio) const {
    QMatrix4x4 proj;
    if (orthographic) {
        float height = 10.0f / scale;
        float width = height * aspectRatio;
        proj.ortho(-width / 2, width / 2, -height / 2, height / 2, nearPlane, farPlane);
    } else {
        proj.perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }
    return proj;
}

QMatrix4x4 Viewport3D::getViewMatrix() const {
    QMatrix4x4 view;
    view.lookAt(cameraPosition, cameraLookAt, cameraUp);
    return view;
}

ModelViewer::ModelViewer()
{
    viewport_.name = "Default Viewport";
    viewport_.cameraPosition = QVector3D(5, 5, 5);
    viewport_.cameraLookAt = QVector3D(0, 0, 0);
    viewport_.cameraUp = QVector3D(0, 1, 0);
    viewport_.orthographic = true;
    viewport_.scale = 100.0;
}

ModelViewer::~ModelViewer() = default;

bool ModelViewer::loadModel(const QString& skpFilePath) {
    model_ = std::make_shared<SKPModel>(skpFilePath);
    if (!model_->load()) {
        model_ = nullptr;
        return false;
    }
    calculateInitialView();
    return true;
}

void ModelViewer::fitViewToModel() {
    if (!model_) return;

    auto bbox_min = model_->boundingBoxMin();
    auto bbox_max = model_->boundingBoxMax();

    QVector3D center = (bbox_min + bbox_max) * 0.5f;
    float radius = (bbox_max - bbox_min).length() * 0.5f;

    viewport_.cameraLookAt = center;
    viewport_.cameraPosition = center + QVector3D(radius, radius, radius).normalized() * radius * 1.5f;
    viewport_.fieldOfView = 45.0;
}

void ModelViewer::resetView() {
    calculateInitialView();
}

void ModelViewer::pan(float dx, float dy) {
    QVector3D forward = (viewport_.cameraLookAt - viewport_.cameraPosition).normalized();
    QVector3D right = QVector3D::crossProduct(forward, viewport_.cameraUp).normalized();
    QVector3D up = viewport_.cameraUp;

    QVector3D offset = (right * dx + up * dy) * 0.01f;
    viewport_.cameraPosition += offset;
    viewport_.cameraLookAt += offset;
}

void ModelViewer::orbit(float deltaX, float deltaY) {
    QVector3D toCamera = viewport_.cameraPosition - viewport_.cameraLookAt;

    // Rotation around Y axis (horizontal)
    QMatrix4x4 yRotation;
    yRotation.rotate(deltaX * 0.5f, 0, 1, 0);
    toCamera = yRotation.map(toCamera);

    // Rotation around X axis (vertical)
    QVector3D right = QVector3D::crossProduct(viewport_.cameraUp, toCamera).normalized();
    QMatrix4x4 xRotation;
    xRotation.rotate(deltaY * 0.5f, right);
    toCamera = xRotation.map(toCamera);

    viewport_.cameraPosition = viewport_.cameraLookAt + toCamera;
}

void ModelViewer::zoom(float factor) {
    viewport_.scale *= (1.0 + factor * 0.1);
    if (viewport_.scale < 0.1) viewport_.scale = 0.1;
    if (viewport_.scale > 1000.0) viewport_.scale = 1000.0;
}

void ModelViewer::calculateInitialView() {
    if (model_ && model_->isLoaded()) {
        fitViewToModel();
    } else {
        viewport_.cameraPosition = QVector3D(5, 5, 5);
        viewport_.cameraLookAt = QVector3D(0, 0, 0);
        viewport_.cameraUp = QVector3D(0, 1, 0);
    }
}
