#pragma once

#include <QString>
#include <vector>

class Sheet;
class Viewport;

class Document {
public:
    explicit Document(QString name = QStringLiteral("Untitled"));

    QString name() const;
    void setName(const QString& name);

    void addSheet(const Sheet& sheet);
    std::vector<Sheet>& sheets();
    const std::vector<Sheet>& sheets() const;

    void addModelReference(const QString& path);
    std::vector<QString> modelReferences() const;

private:
    QString name_;
    std::vector<Sheet> sheets_;
    std::vector<QString> model_references_;
};
