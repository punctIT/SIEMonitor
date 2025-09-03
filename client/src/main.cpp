#include "backend/ServerConection.h"
#include "frontend/gui.hpp"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GUI gui;
    gui.init_window();
    app.exec();
}