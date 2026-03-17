#include <QGuiApplication>

#include "ugar_io_qt/gamewindow.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    GameWindow window;
    window.show();
    return app.exec();
}
