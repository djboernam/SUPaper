#pragma once

#include <QString>
#include <QColor>

struct Point2D {
    double x = 0.0;
    double y = 0.0;
};

class Geometry {
public:
    enum class Type {
        Line,
        Rectangle,
        Text,
        Dimension,
        Viewport,
        PolyLine
    };

    Geometry(Type type = Type::Line);

    Type type() const;
    void setType(Type type);

    QString id() const;
    void setId(const QString& id);

    QString layerName() const;
    void setLayerName(const QString& layerName);

    QColor color() const;
    void setColor(const QColor& color);

    double lineWeight() const;
    void setLineWeight(double weight);

private:
    Type type_ = Type::Line;
    QString id_;
    QString layer_name_ = "Default";
    QColor color_ = QColor(32, 32, 32);
    double line_weight_ = 0.5;
};
