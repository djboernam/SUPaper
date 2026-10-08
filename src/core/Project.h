#pragma once

#include <QString>
#include <vector>

#include "Document.h"

class Project {
public:
    explicit Project(QString name = QStringLiteral("New Project"));

    QString name() const;
    void setName(const QString& name);

    void addDocument(const Document& document);
    std::vector<Document>& documents();
    const std::vector<Document>& documents() const;

private:
    QString name_;
    std::vector<Document> documents_;
};
