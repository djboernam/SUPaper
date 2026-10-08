#include "Document.h"

#include "Sheet.h"

Document::Document(QString name)
    : name_(std::move(name))
{
}

QString Document::name() const {
    return name_;
}

void Document::setName(const QString& name) {
    name_ = name;
}

void Document::addSheet(const Sheet& sheet) {
    sheets_.push_back(sheet);
}

std::vector<Sheet>& Document::sheets() {
    return sheets_;
}

const std::vector<Sheet>& Document::sheets() const {
    return sheets_;
}

void Document::addModelReference(const QString& path) {
    model_references_.push_back(path);
}

std::vector<QString> Document::modelReferences() const {
    return model_references_;
}
