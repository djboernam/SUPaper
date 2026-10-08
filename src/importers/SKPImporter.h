#pragma once

#include <QString>
#include <QVector3D>
#include <vector>
#include <memory>

struct SKPVertex {
    QVector3D position;
    QVector3D normal;
};

struct SKPFace {
    std::vector<int> vertexIndices;
    QString materialName;
};

struct SKPComponent {
    QString name;
    std::vector<SKPVertex> vertices;
    std::vector<SKPFace> faces;
    QVector3D position;
    QVector3D scale;
};

class SKPModel {
public:
    explicit SKPModel(const QString& filePath);
    ~SKPModel();

    bool load();
    bool isLoaded() const { return loaded_; }
    QString filePath() const { return file_path_; }
    QString modelName() const { return model_name_; }

    const std::vector<SKPComponent>& components() const { return components_; }
    QVector3D boundingBoxMin() const { return bbox_min_; }
    QVector3D boundingBoxMax() const { return bbox_max_; }

    void calculateBoundingBox();

private:
    QString file_path_;
    QString model_name_;
    bool loaded_ = false;
    std::vector<SKPComponent> components_;
    QVector3D bbox_min_;
    QVector3D bbox_max_;

    bool parseSKPFile();
    void extractModelInfo();
};
