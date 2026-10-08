#include "SheetCanvas.h"
#include "../core/GeometryLayer.h"
#include "../core/ViewportSystem.h"
#include "../rendering/ModelViewer.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <cmath>

SheetCanvas::SheetCanvas(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #f0f0f0;");
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::CrossCursor);
}

void SheetCanvas::setModelViewer(std::shared_ptr<ModelViewer> viewer) {
    model_viewer_ = viewer;
    update();
}

void SheetCanvas::addShape(std::shared_ptr<GeometryShape> shape) {
    shapes_.push_back(shape);
    update();
}

void SheetCanvas::addViewport(std::shared_ptr<ViewportLayer> viewport) {
    viewports_.push_back(viewport);
    update();
}

void SheetCanvas::clearShapes() {
    shapes_.clear();
    update();
}

void SheetCanvas::clearViewports() {
    viewports_.clear();
    update();
}

void SheetCanvas::zoomIn() {
    zoom_ *= 1.2;
    update();
}

void SheetCanvas::zoomOut() {
    zoom_ /= 1.2;
    update();
}

void SheetCanvas::fitToView() {
    zoom_ = 1.0;
    pan_x_ = 0.0;
    pan_y_ = 0.0;
    update();
}

void SheetCanvas::resetView() {
    fitToView();
}

void SheetCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Apply pan and zoom transformation
    painter.translate(width() / 2.0 + pan_x_, height() / 2.0 + pan_y_);
    painter.scale(zoom_, zoom_);
    painter.translate(-paper_width_ / 2.0, -paper_height_ / 2.0);

    // Draw grid
    drawGrid(painter);

    // Draw sheet paper
    drawSheet(painter);

    // Draw viewports
    drawViewports(painter);

    // Draw shapes
    drawShapes(painter);
}

void SheetCanvas::drawSheet(QPainter& painter) {
    // Draw paper background (white)
    painter.fillRect(0, 0, paper_width_, paper_height_, Qt::white);

    // Draw paper border
    painter.setPen(QPen(Qt::black, 1.0 / zoom_));
    painter.drawRect(0, 0, paper_width_, paper_height_);
}

void SheetCanvas::drawGrid(QPainter& painter) {
    painter.setPen(QPen(QColor(200, 200, 200), 0.5 / zoom_));

    const double grid_size = 10.0;  // 10mm grid

    for (double x = 0; x <= paper_width_; x += grid_size) {
        painter.drawLine(x, 0, x, paper_height_);
    }
    for (double y = 0; y <= paper_height_; y += grid_size) {
        painter.drawLine(0, y, paper_width_, y);
    }
}

void SheetCanvas::drawViewports(QPainter& painter) {
    painter.setPen(QPen(Qt::blue, 2.0 / zoom_));

    for (const auto& viewport : viewports_) {
        double x = viewport->position().x();
        double y = viewport->position().y();
        double w = viewport->width();
        double h = viewport->height();

        // Draw viewport frame
        painter.drawRect(x, y, w, h);

        // Draw viewport label
        painter.setPen(QPen(Qt::blue, 1.0 / zoom_));
        painter.setFont(QFont("Arial", static_cast<int>(10 / zoom_)));
        painter.drawText(x + 5, y + 15, viewport->name());

        // Draw border
        painter.setPen(QPen(Qt::blue, 2.0 / zoom_));
        painter.drawRect(x, y, w, h);
    }
}

void SheetCanvas::drawShapes(QPainter& painter) {
    for (const auto& shape : shapes_) {
        painter.setPen(QPen(shape->color(), shape->lineWeight() / zoom_));

        // Simplified shape drawing
        switch (shape->type()) {
            case GeometryShape::Type::Line: {
                if (auto line = std::dynamic_pointer_cast<Line>(shape)) {
                    painter.drawLine(line->startPoint().toPointF(),
                                   line->endPoint().toPointF());
                }
                break;
            }
            case GeometryShape::Type::Rectangle: {
                if (auto rect = std::dynamic_pointer_cast<Rectangle>(shape)) {
                    painter.drawRect(rect->topLeft().x(), rect->topLeft().y(),
                                   rect->width(), rect->height());
                }
                break;
            }
            case GeometryShape::Type::Circle: {
                if (auto circle = std::dynamic_pointer_cast<Circle>(shape)) {
                    painter.drawEllipse(circle->center().toPointF(), circle->radius(), circle->radius());
                }
                break;
            }
            case GeometryShape::Type::Text: {
                if (auto text = std::dynamic_pointer_cast<TextShape>(shape)) {
                    painter.setFont(QFont("Arial", static_cast<int>(text->fontSize())));
                    painter.drawText(text->position().toPointF(), text->text());
                }
                break;
            }
            default:
                break;
        }
    }
}

void SheetCanvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        is_panning_ = true;
        last_mouse_x_ = event->x();
        last_mouse_y_ = event->y();
    }
}

void SheetCanvas::mouseMoveEvent(QMouseEvent* event) {
    if (is_panning_) {
        int dx = event->x() - last_mouse_x_;
        int dy = event->y() - last_mouse_y_;
        pan_x_ += dx;
        pan_y_ += dy;
        last_mouse_x_ = event->x();
        last_mouse_y_ = event->y();
        update();
    }
}

void SheetCanvas::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        is_panning_ = false;
    }
}

void SheetCanvas::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

void SheetCanvas::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    update();
}
