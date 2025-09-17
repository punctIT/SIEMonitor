#include "login.hpp"
#include "../gui.h" 
#include "../style/style.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>


#include <string>


QWidget * LoginWindow::get_window(){
    QWidget* container = new QWidget();
    container->setAutoFillBackground(true);

    QGridLayout* layout = new QGridLayout(container);
    QLabel *err=new QLabel("",container);
    err->setStyleSheet("color: red; font-size:11px; font-weight: bold; background: transparent;");

    QLabel *title= new QLabel("SIEM Monitor",container);
    title->setAlignment(Qt::AlignCenter);

    QLineEdit *username_entry= new QLineEdit(container);
    QLabel *username=new QLabel("Username:");
    username->setStyleSheet("color: white; font-size:11px; font-weight: bold; background: transparent;");

    QLineEdit *password_entry= new QLineEdit(container);
    password_entry->setEchoMode(QLineEdit::Password);

    QLabel *password=new QLabel("Password:");
    password->setStyleSheet("color: white; font-size:11px; font-weight: bold; background: transparent;");

    
    QPushButton *login_btn = new QPushButton("Login",container);
    QPushButton *btn = new QPushButton("auto",container);
    QObject::connect(&gui.get_server(), &ServerConection::loginResponse,
                    [this,username_entry,password_entry,err,layout](QString resp){
        qDebug()<<resp<<"\n";
        if (resp == "Login Succesul") {
            //qDebug()<<username_entry->text();
            gui.set_siem_window(username_entry->text());
        }
        else {
            username_entry->setText("");
            password_entry->setText("");
            
            err->setText(resp);
            layout->addWidget(err,5,0);
            qDebug() << "Login failed!";
        }
    });
    QObject::connect(login_btn, &QPushButton::clicked, [this,username_entry,password_entry](){
        std::string cmd = "login " + username_entry->text().toStdString() + " " +
                        password_entry->text().toStdString();
        gui.get_server().sent(cmd);
    });
    QObject::connect(btn, &QPushButton::clicked, [this,username_entry,password_entry](){
        username_entry->setText("DexterMorgan");
        password_entry->setText("password");
        std::string cmd = "login " + username_entry->text().toStdString() + " " + password_entry->text().toStdString();
        gui.get_server().sent(cmd);
    });

    container->setStyleSheet(login_style());
    layout->addWidget(title,0,0);
    layout->addWidget(username,1,0);  
    layout->addWidget(username_entry,2,0);  
    layout->addWidget(password,3,0);          
    layout->addWidget(password_entry,4,0);  
    layout->addWidget(login_btn,6,0);   
    layout->addWidget(btn,6,1);   
    
    return container;
}

