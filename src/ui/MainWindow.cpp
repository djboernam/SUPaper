#include "MainWindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTextEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("SUPaper V0.1");
    buildUi();
}

void MainWindow::buildUi() {
    auto* central = new QWidget(this);
    auto* rootLayout = new QHBoxLayout(central);

    splitter_ = new QSplitter(Qt::Horizontal, this);

    auto* leftPanel = new QWidget(this);
    auto* leftLayout = new QVBoxLayout(leftPanel);

    newDocButton_ = new QPushButton("New Document", this);
    saveButton_ = new QPushButton("Save", this);
    leftLayout->addWidget(newDocButton_);
    leftLayout->addWidget(saveButton_);

    sheetsTree_ = new QTreeWidget(this);
    sheetsTree_->setHeaderLabel("Project");
    auto* rootItem = new QTreeWidgetItem(sheetsTree_);
    rootItem->setText(0, "SUPaper Project");

    auto* sheetItem = new QTreeWidgetItem(rootItem);
    sheetItem->setText(0, "Sheet A101");

    auto* referencesItem = new QTreeWidgetItem(rootItem);
    referencesItem->setText(0, "Model References");

    leftLayout->addWidget(sheetsTree_);

    auto* canvasPanel = new QWidget(this);
    auto* canvasLayout = new QVBoxLayout(canvasPanel);

    titleLabel_ = new QLabel("SketchUp Documentation Workspace", this);
    titleLabel_->setStyleSheet("font-size: 20px; font-weight: 600;");
    canvasLayout->addWidget(titleLabel_);

    auto* canvas = new QTextEdit(this);
    canvas->setPlainText("SUPaper V0.1\n\nThis is the initial native application skeleton.\n\nNext steps:\n- add document engine\n- add geometry layer\n- add viewport system\n- add Ruby extension API\n- add PDF export");
    canvas->setReadOnly(true);
    canvasLayout->addWidget(canvas);

    statusLabel_ = new QLabel("Ready", this);
    canvasLayout->addWidget(statusLabel_);

    splitter_->addWidget(leftPanel);
    splitter_->addWidget(canvasPanel);
    splitter_->setSizes({280, 1000});

    rootLayout->addWidget(splitter_);
    setCentralWidget(central);
}
