#include "RubyExtensionAPI.h"

RubyExtensionAPI::RubyExtensionAPI() = default;

void RubyExtensionAPI::registerCommand(const QString& name, std::function<void()> handler) {
    commands_.emplace_back(name, handler);
}

void RubyExtensionAPI::executeCommand(const QString& name) {
    for (const auto& cmd : commands_) {
        if (cmd.first == name) {
            cmd.second();
            return;
        }
    }
}

bool RubyExtensionAPI::hasCommand(const QString& name) const {
    for (const auto& cmd : commands_) {
        if (cmd.first == name) {
            return true;
        }
    }
    return false;
}

void RubyExtensionAPI::createSheetCommand(const QString& sheetName, const QString& size) {
    Q_UNUSED(sheetName);
    Q_UNUSED(size);
}

void RubyExtensionAPI::deleteSheetCommand(const QString& sheetName) {
    Q_UNUSED(sheetName);
}

void RubyExtensionAPI::createViewportCommand(const QString& modelPath, const QString& sceneName) {
    Q_UNUSED(modelPath);
    Q_UNUSED(sceneName);
}

void RubyExtensionAPI::exportPdfCommand(const QString& outputPath) {
    Q_UNUSED(outputPath);
}

void RubyExtensionAPI::exportSvgCommand(const QString& outputPath) {
    Q_UNUSED(outputPath);
}

QStringList RubyExtensionAPI::registeredCommands() const {
    QStringList result;
    for (const auto& cmd : commands_) {
        result.append(cmd.first);
    }
    return result;
}
