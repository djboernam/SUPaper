#pragma once

#include <QString>
#include <QDateTime>
#include <vector>
#include <memory>

class Sheet;
class Layer;

class DocumentEngine {
public:
    DocumentEngine();
    ~DocumentEngine();

    // Document lifecycle
    bool createNewDocument(const QString& name);
    bool openDocument(const QString& path);
    bool saveDocument(const QString& path);
    bool closeDocument();

    // Document properties
    QString documentName() const;
    QString documentPath() const;
    void setDocumentName(const QString& name);
    bool isModified() const;
    void setModified(bool modified);

    // Sheet management
    std::shared_ptr<Sheet> createSheet(const QString& name, const QString& size = "A3");
    std::shared_ptr<Sheet> currentSheet() const;
    void setCurrentSheet(std::shared_ptr<Sheet> sheet);
    std::vector<std::shared_ptr<Sheet>> allSheets() const;
    bool deleteSheet(std::shared_ptr<Sheet> sheet);

    // Layer management
    std::shared_ptr<Layer> createLayer(const QString& name);
    std::vector<std::shared_ptr<Layer>> allLayers() const;
    bool deleteLayer(std::shared_ptr<Layer> layer);

    // Undo/Redo
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;

    // Export
    bool exportToPdf(const QString& path);
    bool exportToSvg(const QString& path);

private:
    QString document_name_;
    QString document_path_;
    bool modified_ = false;
    std::vector<std::shared_ptr<Sheet>> sheets_;
    std::vector<std::shared_ptr<Layer>> layers_;
    std::shared_ptr<Sheet> current_sheet_;
    std::vector<QString> undo_stack_;
    std::vector<QString> redo_stack_;
};
