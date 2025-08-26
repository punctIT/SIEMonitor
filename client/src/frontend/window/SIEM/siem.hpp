
#pragma once
#include <QtWidgets/QWidget>

class GUI;

class SIEMWindow{
private:
    GUI& gui;
public:
    SIEMWindow(GUI &srv) : gui(srv) {}
    QWidget* get_window();
};
