#include "PdfExporter.h"

#include <QPainter>

PdfExporter::PdfExporter(const QString& outputPath)
    : output_path_(outputPath)
{
    pdf_writer_ = std::make_unique<QPdfWriter>(outputPath);
    pdf_writer_->setPageSize(QPageSize(QPageSize::A4));
    pdf_writer_->setResolution(300);
}

bool PdfExporter::exportSheet(const QString& sheetName) {
    if (!pdf_writer_) {
        return false;
    }

    QPainter painter(pdf_writer_.get());
    if (!painter.isActive()) {
        return false;
    }

    painter.drawText(50, 50, sheetName);
    painter.end();

    return true;
}

bool PdfExporter::exportAllSheets() {
    return true;
}

bool PdfExporter::finalize() {
    return true;
}
