#include "SKPImporter.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <cstring>
#include <limits>

SKPModel::SKPModel(const QString& filePath)
    : file_path_(filePath)
{
    QFileInfo info(filePath);
    model_name_ = info.baseName();
}

SKPModel::~SKPModel() = default;

bool SKPModel::load() {
    QFile file(file_path_);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open SKP file:" << file_path_;
        return false;
    }

    // Read SKP header (simplified)
    char header[16];
    if (file.read(header, 16) != 16) {
        qWarning() << "Invalid SKP file header";
        return false;
    }

    // Verify SKP signature (starts with "SketchUp Model")
    if (std::string(header, 8) != "SketchUp") {
        qWarning() << "Not a valid SketchUp file";
        return false;
    }

    file.close();

    // For now, create a placeholder component
    // Full SKP parsing requires the SketchUp SDK
    SKPComponent defaultComponent;
    defaultComponent.name = model_name_;
    defaultComponent.position = QVector3D(0, 0, 0);
    defaultComponent.scale = QVector3D(1, 1, 1);

    // Add sample vertices for a simple box
    defaultComponent.vertices.push_back({QVector3D(0, 0, 0), QVector3D(0, 0, -1)});
    defaultComponent.vertices.push_back({QVector3D(1, 0, 0), QVector3D(0, 0, -1)});
    defaultComponent.vertices.push_back({QVector3D(1, 1, 0), QVector3D(0, 0, -1)});
    defaultComponent.vertices.push_back({QVector3D(0, 1, 0), QVector3D(0, 0, -1)});

    SKPFace face;
    face.vertexIndices = {0, 1, 2, 3};
    face.materialName = "Default";
    defaultComponent.faces.push_back(face);

    components_.push_back(defaultComponent);
    calculateBoundingBox();
    loaded_ = true;

    return true;
}

void SKPModel::calculateBoundingBox() {
    bbox_min_ = QVector3D(std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max());
    bbox_max_ = QVector3D(std::numeric_limits<float>::lowest(),
                         std::numeric_limits<float>::lowest(),
                         std::numeric_limits<float>::lowest());

    for (const auto& component : components_) {
        for (const auto& vertex : component.vertices) {
            bbox_min_.setX(std::min(bbox_min_.x(), vertex.position.x()));
            bbox_min_.setY(std::min(bbox_min_.y(), vertex.position.y()));
            bbox_min_.setZ(std::min(bbox_min_.z(), vertex.position.z()));

            bbox_max_.setX(std::max(bbox_max_.x(), vertex.position.x()));
            bbox_max_.setY(std::max(bbox_max_.y(), vertex.position.y()));
            bbox_max_.setZ(std::max(bbox_max_.z(), vertex.position.z()));
        }
    }
}
