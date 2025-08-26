
#pragma once
#include <QtWidgets/QGridLayout>

class GUI;

class SIEMWindow{
private:
    GUI& gui;
public:
    SIEMWindow(GUI &srv) : gui(srv) {}
    QGridLayout* get_window(QWidget *parent);
};
