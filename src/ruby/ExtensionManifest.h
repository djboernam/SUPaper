#pragma once

#include <QString>
#include <QList>

class ExtensionManifest {
public:
    ExtensionManifest();

    QString name() const;
    void setName(const QString& name);

    QString version() const;
    void setVersion(const QString& version);

    QString entryPoint() const;
    void setEntryPoint(const QString& entryPoint);

    QStringList permissions() const;
    void setPermissions(const QStringList& permissions);

private:
    QString name_;
    QString version_;
    QString entry_point_;
    QStringList permissions_;
};
