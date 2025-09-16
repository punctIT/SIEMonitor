#pragma once

#include "../backend/ServerConection.h"
#include "window/login.hpp"
#include "window/siem.h"
#include "window/ip_connect.hpp"
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
        ConnectWindow *server_connect;

    public:
        GUI();
        ~GUI();
        GUI& init_window();
        ServerConection& get_server();
        GUI& set_siem_window(QString user);
        GUI& set_login_window();
        GUI& set_connect_window();
};

