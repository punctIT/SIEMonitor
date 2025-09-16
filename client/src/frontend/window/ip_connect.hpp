
#pragma once
#include <QtWidgets/QWidget>

class GUI;

class ConnectWindow{
private:
    GUI& gui;
public:
    ConnectWindow(GUI &srv) : gui(srv) {}
    QWidget* get_window();
};
