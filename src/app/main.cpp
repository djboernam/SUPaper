#include <QApplication>

#include "app/App.h"
#include "ui/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("SUPaper");
    app.setApplicationVersion("0.1.0");

    MainWindow window;
    window.resize(1280, 820);
    window.show();

    return app.exec();
}
