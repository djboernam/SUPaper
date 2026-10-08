#pragma once

#include <QString>
#include <QStringList>
#include <vector>
#include <functional>

class RubyExtensionAPI {
public:
    RubyExtensionAPI();

    // Document operations
    void registerCommand(const QString& name, std::function<void()> handler);
    void executeCommand(const QString& name);
    bool hasCommand(const QString& name) const;

    // Sheet operations
    void createSheetCommand(const QString& sheetName, const QString& size);
    void deleteSheetCommand(const QString& sheetName);

    // Viewport operations
    void createViewportCommand(const QString& modelPath, const QString& sceneName);

    // Export operations
    void exportPdfCommand(const QString& outputPath);
    void exportSvgCommand(const QString& outputPath);

    // Extension metadata
    QStringList registeredCommands() const;

private:
    std::vector<std::pair<QString, std::function<void()>>> commands_;
};
