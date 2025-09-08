#pragma once

#include "../backend/ServerConection.h"
#include "window/login.hpp"
//#include "window/home_screen/siem_home.h"
#include "window/siem.h"
#include <QtWidgets/QMainWindow>
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

