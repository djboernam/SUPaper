#pragma once

#include <QString>
#include <vector>

class Document;

class App {
public:
    static App& instance();

    Document& createDocument(const QString& name);
    std::vector<Document>& documents();
    bool loadProject(const QString& path);
    bool saveProject(const QString& path);
    bool openLastProject();

private:
    App();
    ~App();

    std::vector<Document> documents_;
};
