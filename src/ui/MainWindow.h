#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void buildUi();

    QSplitter* splitter_;
    QTreeWidget* sheetsTree_;
    QLabel* titleLabel_;
    QLabel* statusLabel_;
    QPushButton* newDocButton_;
    QPushButton* saveButton_;
};
