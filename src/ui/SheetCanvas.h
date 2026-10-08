#pragma once

#include <QWidget>
#include <QPainter>
#include <memory>
#include <vector>

class GeometryShape;
class ViewportLayer;
class ModelViewer;

class SheetCanvas : public QWidget {
    Q_OBJECT

public:
    explicit SheetCanvas(QWidget* parent = nullptr);

    void setModelViewer(std::shared_ptr<ModelViewer> viewer);
    void addShape(std::shared_ptr<GeometryShape> shape);
    void addViewport(std::shared_ptr<ViewportLayer> viewport);
    void clearShapes();
    void clearViewports();

    void zoomIn();
    void zoomOut();
    void fitToView();
    void resetView();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void drawSheet(QPainter& painter);
    void drawViewports(QPainter& painter);
    void drawShapes(QPainter& painter);
    void drawGrid(QPainter& painter);

    std::shared_ptr<ModelViewer> model_viewer_;
    std::vector<std::shared_ptr<GeometryShape>> shapes_;
    std::vector<std::shared_ptr<ViewportLayer>> viewports_;

    double zoom_ = 1.0;
    double pan_x_ = 0.0;
    double pan_y_ = 0.0;

    bool is_panning_ = false;
    int last_mouse_x_ = 0;
    int last_mouse_y_ = 0;

    // Paper size in millimeters (A3 = 297x420)
    double paper_width_ = 297.0;
    double paper_height_ = 420.0;
};
