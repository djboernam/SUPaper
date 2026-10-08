#include "Project.h"

Project::Project(QString name)
    : name_(std::move(name))
{
}

QString Project::name() const {
    return name_;
}

void Project::setName(const QString& name) {
    name_ = name;
}

void Project::addDocument(const Document& document) {
    documents_.push_back(document);
}

std::vector<Document>& Project::documents() {
    return documents_;
}

const std::vector<Document>& Project::documents() const {
    return documents_;
}
