#pragma once

#include <QString>

class Viewport {
public:
    Viewport();

    QString id;
    QString name;
    QString modelPath;
    QString sceneName;
    double x = 0.0;
    double y = 0.0;
    double width = 200.0;
    double height = 120.0;
    double scale = 100.0;
    QString projection = QStringLiteral("orthographic");
};
