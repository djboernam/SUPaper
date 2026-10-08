#pragma once

#include <QString>
#include <QColor>

class Layer {
public:
    Layer(QString name = QStringLiteral("Default"), QColor color = QColor(80, 80, 80));

    QString name() const;
    void setName(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    bool visible() const;
    void setVisible(bool visible);

    bool locked() const;
    void setLocked(bool locked);

private:
    QString name_;
    QColor color_;
    bool visible_ = true;
    bool locked_ = false;
};
