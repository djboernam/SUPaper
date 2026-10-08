#include "ExtensionManifest.h"

ExtensionManifest::ExtensionManifest() = default;

QString ExtensionManifest::name() const { return name_; }
void ExtensionManifest::setName(const QString& name) { name_ = name; }

QString ExtensionManifest::version() const { return version_; }
void ExtensionManifest::setVersion(const QString& version) { version_ = version; }

QString ExtensionManifest::entryPoint() const { return entry_point_; }
void ExtensionManifest::setEntryPoint(const QString& entryPoint) { entry_point_ = entryPoint; }

QStringList ExtensionManifest::permissions() const { return permissions_; }
void ExtensionManifest::setPermissions(const QStringList& permissions) { permissions_ = permissions; }
