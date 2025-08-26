
#pragma once
#include <QtWidgets/QWidget>

class GUI;

class LoginWindow{
private:
    GUI& gui;
public:
    LoginWindow(GUI &srv) : gui(srv) {}
    QWidget* get_window();
};
