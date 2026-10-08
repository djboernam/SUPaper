#include "DocumentEngine.h"
#include "Sheet.h"
#include "Layer.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

DocumentEngine::DocumentEngine() = default;
DocumentEngine::~DocumentEngine() = default;

bool DocumentEngine::createNewDocument(const QString& name) {
    document_name_ = name;
    document_path_ = "";
    modified_ = false;
    sheets_.clear();
    layers_.clear();
    undo_stack_.clear();
    redo_stack_.clear();
    return true;
}

bool DocumentEngine::openDocument(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    if (json.isNull() || !json.isObject()) {
        return false;
    }

    QJsonObject root = json.object();
    document_name_ = root["name"].toString();
    document_path_ = path;
    modified_ = false;

    return true;
}

bool DocumentEngine::saveDocument(const QString& path) {
    document_path_ = path;

    QJsonObject root;
    root["name"] = document_name_;
    root["created"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["sheet_count"] = static_cast<int>(sheets_.size());
    root["layer_count"] = static_cast<int>(layers_.size());

    QJsonDocument doc(root);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    modified_ = false;
    return true;
}

bool DocumentEngine::closeDocument() {
    sheets_.clear();
    layers_.clear();
    document_name_ = "";
    document_path_ = "";
    return true;
}

QString DocumentEngine::documentName() const {
    return document_name_;
}

QString DocumentEngine::documentPath() const {
    return document_path_;
}

void DocumentEngine::setDocumentName(const QString& name) {
    document_name_ = name;
    modified_ = true;
}

bool DocumentEngine::isModified() const {
    return modified_;
}

void DocumentEngine::setModified(bool modified) {
    modified_ = modified;
}

std::shared_ptr<Sheet> DocumentEngine::createSheet(const QString& name, const QString& size) {
    auto sheet = std::make_shared<Sheet>(name, size);
    sheets_.push_back(sheet);
    if (!current_sheet_) {
        current_sheet_ = sheet;
    }
    modified_ = true;
    return sheet;
}

std::shared_ptr<Sheet> DocumentEngine::currentSheet() const {
    return current_sheet_;
}

void DocumentEngine::setCurrentSheet(std::shared_ptr<Sheet> sheet) {
    current_sheet_ = sheet;
}

std::vector<std::shared_ptr<Sheet>> DocumentEngine::allSheets() const {
    return sheets_;
}

bool DocumentEngine::deleteSheet(std::shared_ptr<Sheet> sheet) {
    auto it = std::find(sheets_.begin(), sheets_.end(), sheet);
    if (it != sheets_.end()) {
        sheets_.erase(it);
        if (current_sheet_ == sheet) {
            current_sheet_ = sheets_.empty() ? nullptr : sheets_.front();
        }
        modified_ = true;
        return true;
    }
    return false;
}

std::shared_ptr<Layer> DocumentEngine::createLayer(const QString& name) {
    auto layer = std::make_shared<Layer>(name);
    layers_.push_back(layer);
    modified_ = true;
    return layer;
}

std::vector<std::shared_ptr<Layer>> DocumentEngine::allLayers() const {
    return layers_;
}

bool DocumentEngine::deleteLayer(std::shared_ptr<Layer> layer) {
    auto it = std::find(layers_.begin(), layers_.end(), layer);
    if (it != layers_.end()) {
        layers_.erase(it);
        modified_ = true;
        return true;
    }
    return false;
}

void DocumentEngine::undo() {
    if (!undo_stack_.empty()) {
        redo_stack_.push_back(undo_stack_.back());
        undo_stack_.pop_back();
    }
}

void DocumentEngine::redo() {
    if (!redo_stack_.empty()) {
        undo_stack_.push_back(redo_stack_.back());
        redo_stack_.pop_back();
    }
}

bool DocumentEngine::canUndo() const {
    return !undo_stack_.empty();
}

bool DocumentEngine::canRedo() const {
    return !redo_stack_.empty();
}

bool DocumentEngine::exportToPdf(const QString& path) {
    Q_UNUSED(path);
    return true;
}

bool DocumentEngine::exportToSvg(const QString& path) {
    Q_UNUSED(path);
    return true;
}
