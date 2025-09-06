
#pragma once
#include <QtWidgets/QMainWindow>
#include "../backend/ServerConection.h"
#include "window/login.hpp"
#include "window/SIEM/siem.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QObject>


class GUI: public QObject {  
    Q_OBJECT  
    private:
        ServerConection server;
        QStackedWidget *stack;
        QMainWindow *window;
        SIEMWindow *siem;
        LoginWindow *login;
    public:
        GUI();
        ~GUI();
        GUI& init_window();
        ServerConection& get_server();
        GUI& set_siem_window();
        GUI& set_login_window();
};

