#pragma once

#include <QString>
#include <QVector2D>
#include <QColor>
#include <vector>
#include <memory>

class GeometryShape {
public:
    enum class Type {
        Line,
        Polyline,
        Rectangle,
        Circle,
        Arc,
        Text,
        Dimension
    };

    explicit GeometryShape(Type type);
    virtual ~GeometryShape() = default;

    Type type() const { return type_; }
    QString id() const { return id_; }
    QColor color() const { return color_; }
    void setColor(const QColor& color) { color_ = color; }
    double lineWeight() const { return line_weight_; }
    void setLineWeight(double weight) { line_weight_ = weight; }
    QString layer() const { return layer_; }
    void setLayer(const QString& layer) { layer_ = layer; }

 protected:
    Type type_;
    QString id_;
    QColor color_ = QColor(0, 0, 0);
    double line_weight_ = 0.5;
    QString layer_ = "Default";
};

class Line : public GeometryShape {
public:
    Line(QVector2D start, QVector2D end);
    QVector2D startPoint() const { return start_; }
    QVector2D endPoint() const { return end_; }

private:
    QVector2D start_;
    QVector2D end_;
};

class Rectangle : public GeometryShape {
public:
    Rectangle(QVector2D topLeft, double width, double height);
    QVector2D topLeft() const { return top_left_; }
    double width() const { return width_; }
    double height() const { return height_; }

private:
    QVector2D top_left_;
    double width_;
    double height_;
};

class Circle : public GeometryShape {
public:
    Circle(QVector2D center, double radius);
    QVector2D center() const { return center_; }
    double radius() const { return radius_; }

private:
    QVector2D center_;
    double radius_;
};

class TextShape : public GeometryShape {
public:
    TextShape(const QString& text, QVector2D position);
    QString text() const { return text_; }
    QVector2D position() const { return position_; }
    double fontSize() const { return font_size_; }
    void setFontSize(double size) { font_size_ = size; }

private:
    QString text_;
    QVector2D position_;
    double font_size_ = 12.0;
};

class GeometryLayer {
public:
    explicit GeometryLayer(const QString& name);

    QString name() const { return name_; }
    void addShape(std::shared_ptr<GeometryShape> shape);
    std::vector<std::shared_ptr<GeometryShape>> shapes() const { return shapes_; }
    bool removeShape(std::shared_ptr<GeometryShape> shape);
    void clear();

private:
    QString name_;
    std::vector<std::shared_ptr<GeometryShape>> shapes_;
};
