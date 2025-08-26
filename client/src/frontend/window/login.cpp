#include "login.hpp"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include "../gui.hpp" 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <string>

QGridLayout * LoginWindow::get_window(QWidget *parent){
    QLineEdit *username= new QLineEdit(parent);
    QLineEdit *password= new QLineEdit(parent);
    QPushButton *btn2 = new QPushButton("Login",parent);
    QObject::connect(btn2, &QPushButton::clicked, [this,username,password](){
        std::string cmd="login ";
        cmd+=username->text().toStdString();cmd+=" ";
        cmd+=password->text().toStdString();
        gui.get_server().sent(cmd.c_str());
        qDebug()<<QString::fromStdString(cmd)<<"\n";
        auto response = gui.get_server().get_response();
        while(response.has_value()==false){
            response = gui.get_server().get_response();
        }
        if(response.value()=="Login Succesul"){
            gui.set_siem_window();
        }
        else {
            qDebug()<<"error ";
        }
    });
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(username, 1, 0);        
    layout->addWidget(password ,2, 0);  
    layout->addWidget(btn2,3, 0);   
    return layout;
}