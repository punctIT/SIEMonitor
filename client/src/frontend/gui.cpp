#include "gui.h"
#include "style/style.h"

#include <QtWidgets/QApplication>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QDebug>




GUI::GUI(){

    // server.set_server_adress("127.0.0.1")
    //       .set_server_port(12345)
    //       .configure_connection();
    // server.receive_start();
}
GUI::~GUI(){

}
GUI& GUI::init_window(){
    int argc = 0;
    char *argv[] = {};
    window=new QMainWindow();  

    window->setStyleSheet(main_style());
    window->setFixedSize(400, 200);
    
    siem = new SIEMWindow(*this,window);
    server_connect= new ConnectWindow(*this);

    login = new LoginWindow(*this);

    stack = new QStackedWidget();
    window->setWindowTitle("Security Information and Event Management");
    stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    stack->addWidget(server_connect->get_window());
    stack->addWidget(login->get_window());
    stack->addWidget(siem->get_window());


    
    window->setCentralWidget(stack);
    window->show();
    window->resize(400, 200);
    return *this;
}

GUI& GUI::set_login_window() {
    stack->setCurrentIndex(1); 
    return *this;
}
GUI& GUI::set_connect_window() {
    stack->setCurrentIndex(0); 
    return *this;
}

GUI& GUI::set_siem_window(QString user) {
    siem->set_username(user).start_home_thread();
    stack->setCurrentIndex(2); 
    window->showMaximized();
    return *this;
}


ServerConection& GUI::get_server(){
    return server;
}


