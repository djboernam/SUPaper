#pragma once

#include <QString>
#include <QPdfWriter>
#include <memory>

class PdfExporter {
public:
    explicit PdfExporter(const QString& outputPath);

    bool exportSheet(const QString& sheetName);
    bool exportAllSheets();
    bool finalize();

private:
    QString output_path_;
    std::unique_ptr<QPdfWriter> pdf_writer_;
};
