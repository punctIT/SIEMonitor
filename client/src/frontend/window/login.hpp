
#pragma once
#include <QtWidgets/QGridLayout>

class GUI;

class LoginWindow{
private:
    GUI& gui;
public:
    LoginWindow(GUI &srv) : gui(srv) {}
    QGridLayout* get_window(QWidget *parent);
};
