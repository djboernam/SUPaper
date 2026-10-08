#pragma once

#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QMatrix4x4>
#include <vector>
#include <memory>

class SKPModel;

struct Viewport3D {
    QString name;
    QVector3D cameraPosition;
    QVector3D cameraLookAt;
    QVector3D cameraUp;
    double fieldOfView = 45.0;
    double nearPlane = 0.1;
    double farPlane = 10000.0;
    bool orthographic = false;
    double scale = 1.0;

    QMatrix4x4 getProjectionMatrix(float aspectRatio) const;
    QMatrix4x4 getViewMatrix() const;
};

class ModelViewer {
public:
    ModelViewer();
    ~ModelViewer();

    bool loadModel(const QString& skpFilePath);
    bool isModelLoaded() const { return model_ != nullptr; }
    std::shared_ptr<SKPModel> getModel() const { return model_; }

    // Viewport control
    Viewport3D& getViewport() { return viewport_; }
    const Viewport3D& getViewport() const { return viewport_; }

    void fitViewToModel();
    void resetView();

    // Camera controls
    void pan(float dx, float dy);
    void orbit(float deltaX, float deltaY);
    void zoom(float factor);

private:
    std::shared_ptr<SKPModel> model_;
    Viewport3D viewport_;

    void calculateInitialView();
};
