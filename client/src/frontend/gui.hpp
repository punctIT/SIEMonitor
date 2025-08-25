
#pragma once
#include <QtWidgets/QMainWindow>
#include "../backend/ServerConection.h"
#include "window/login.hpp"
#include "window/siem.hpp"

class GUI{
    private:
        ServerConection server;
        QWidget *central;
        
        SIEMWindow *siem;
        LoginWindow *login;
    public:
        GUI();
        GUI& init_window();
        ServerConection& get_server();
        GUI& set_siem_window();
        GUI& set_login_window();
};
