#pragma once

#include <QString>
#include <QVector2D>
#include <vector>
#include <memory>

class ViewportLayer {
public:
    explicit ViewportLayer(const QString& name);

    QString name() const { return name_; }
    QString modelPath() const { return model_path_; }
    void setModelPath(const QString& path) { model_path_ = path; }

    QString sceneName() const { return scene_name_; }
    void setSceneName(const QString& scene) { scene_name_ = scene; }

    double scale() const { return scale_; }
    void setScale(double scale) { scale_ = scale; }

    QVector2D position() const { return position_; }
    void setPosition(QVector2D pos) { position_ = pos; }

    double width() const { return width_; }
    double height() const { return height_; }
    void setSize(double width, double height) { width_ = width; height_ = height; }

    bool isVisible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }

    QString projection() const { return projection_; }
    void setProjection(const QString& proj) { projection_ = proj; }

private:
    QString name_;
    QString model_path_;
    QString scene_name_;
    double scale_ = 1.0;
    QVector2D position_;
    double width_ = 200.0;
    double height_ = 120.0;
    bool visible_ = true;
    QString projection_ = "orthographic";
};

class ViewportSystem {
public:
    ViewportSystem();

    std::shared_ptr<ViewportLayer> createViewport(const QString& name);
    bool deleteViewport(std::shared_ptr<ViewportLayer> viewport);
    std::vector<std::shared_ptr<ViewportLayer>> allViewports() const { return viewports_; }
    int viewportCount() const { return viewports_.size(); }

private:
    std::vector<std::shared_ptr<ViewportLayer>> viewports_;
};
