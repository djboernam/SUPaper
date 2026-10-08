#pragma once

#include <QString>
#include <QPdfWriter>
#include <memory>

class SheetCanvas;
class DocumentEngine;

class SheetRenderer {
public:
    explicit SheetRenderer(std::shared_ptr<DocumentEngine> engine);

    bool renderSheet(const QString& sheetName, const QString& outputPath);
    bool renderAllSheets(const QString& outputDir);
    bool renderToPdf(const QString& outputPath);

private:
    std::shared_ptr<DocumentEngine> engine_;

    void drawSheetContent(QPainter& painter, const QString& sheetName);
};
