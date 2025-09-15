#include "gui.h"

#include <QtWidgets/QApplication>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QDebug>




GUI::GUI(){

    server.set_server_adress("127.0.0.1")
          .set_server_port(12345)
          .configure_connection();
    server.receive_start();
}
GUI::~GUI(){

}
GUI& GUI::init_window(){
    int argc = 0;
    char *argv[] = {};
    window=new QMainWindow();  

    siem = new SIEMWindow(*this,window);


    login = new LoginWindow(*this);

    stack = new QStackedWidget();
    window->setWindowTitle("SIEM Dashboard");
    
    stack->addWidget(login->get_window());
    stack->addWidget(siem->get_window());


    
    window->setCentralWidget(stack);
    window->resize(400, 200);
    window->show();
    
    return *this;
}

GUI& GUI::set_login_window() {
    stack->setCurrentIndex(0); 
    return *this;
}

GUI& GUI::set_siem_window(QString user) {
    siem->set_username(user).start_home_thread();
    stack->setCurrentIndex(1); 
    window->showMaximized();
    return *this;
}


ServerConection& GUI::get_server(){
    return server;
}


