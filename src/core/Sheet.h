#pragma once

#include <QString>
#include <vector>

class Viewport;

class Sheet {
public:
    Sheet(QString name = QStringLiteral("Sheet"),
          QString size = QStringLiteral("A3"),
          QString orientation = QStringLiteral("portrait"));

    QString name() const;
    QString size() const;
    QString orientation() const;

    void addViewport(const Viewport& viewport);
    std::vector<Viewport>& viewports();
    const std::vector<Viewport>& viewports() const;

private:
    QString name_;
    QString size_;
    QString orientation_;
    std::vector<Viewport> viewports_;
};
