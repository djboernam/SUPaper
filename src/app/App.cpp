#include "App.h"

#include "core/Document.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

App::App() = default;
App::~App() = default;

App& App::instance() {
    static App app;
    return app;
}

Document& App::createDocument(const QString& name) {
    documents_.emplace_back(Document(name));
    return documents_.back();
}

std::vector<Document>& App::documents() {
    return documents_;
}

bool App::loadProject(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    const auto json = QJsonDocument::fromJson(file.readAll());
    if (json.isNull() || !json.isObject()) {
        return false;
    }

    const auto root = json.object();
    auto name = root["name"].toString();
    documents_.emplace_back(Document(name));
    return true;
}

bool App::saveProject(const QString& path) {
    if (documents_.empty()) {
        return false;
    }

    QJsonObject root;
    root["name"] = documents_.front().name();
    root["sheet_count"] = static_cast<int>(documents_.front().sheets().size());

    QJsonDocument doc(root);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

bool App::openLastProject() {
    return false;
}
