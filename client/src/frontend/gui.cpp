#include "gui.hpp"
#include <QtWidgets/QApplication>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <iostream>


GUI::GUI(){
    server.set_server_adress("127.0.0.1")
          .set_server_port(12345)
          .configure_connection();

    server.receive_start();
}

GUI& GUI::init_window(){
    int argc = 0;
    char *argv[] = {};
    QApplication app(argc, argv);
    QMainWindow window;

    siem = new SIEMWindow(*this);
    login = new LoginWindow(*this);

    central = new QWidget;
    window.setWindowTitle("SIEM Dashboard");
    set_login_window();

    
    window.setCentralWidget(central); 
    window.resize(400, 200);
    window.show();
    app.exec();
    return *this;
}
GUI& GUI::set_login_window(){
    delete central->layout(); 
    central->setLayout(login->get_window(central));
    return *this;
}
GUI& GUI::set_siem_window(){
    delete central->layout(); 
    central->setLayout(siem->get_window(central));
    return *this;
}
ServerConection& GUI::get_server(){
    return server;
}