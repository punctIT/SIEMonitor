#include "ip_connect.hpp"
#include "../gui.h" 
#include "../style/style.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>


#include <string>




QWidget * ConnectWindow::get_window(){
    QWidget* container = new QWidget();
    container->setAutoFillBackground(true);

    QGridLayout* layout = new QGridLayout(container);
    QLabel *err=new QLabel("",container);
    err->setStyleSheet("color: red; font-size:11px; font-weight: bold; background: transparent;");

    QLabel *title= new QLabel("SIEM Monitor",container);
    title->setAlignment(Qt::AlignCenter);

    QLineEdit *ip_entry= new QLineEdit(container);
    QLabel *ip=new QLabel("IP:");
    ip->setStyleSheet("color: white; font-size:11px; font-weight: bold; background: transparent;");

    QLineEdit *port_entry= new QLineEdit(container);

    QLabel *port=new QLabel("PORT:");
    port->setStyleSheet("color: white; font-size:11px; font-weight: bold; background: transparent;");

    
    QPushButton *login_btn = new QPushButton("Connect",container);
    QPushButton *btn = new QPushButton("auto",container);
     QObject::connect(btn, &QPushButton::clicked, [this,ip_entry,port_entry,err,layout](){
        try{
            gui.get_server().set_server_adress("127.0.0.9")
                            .set_server_port(12345)
                            .configure_connection()
                            .receive_start();
            gui.set_login_window();
        }
        catch (std::exception &e) {
            ip_entry->setText("");
            port_entry->setText("");
            
            err->setText(e.what());
            layout->addWidget(err,5,0);
            qDebug() << "Login failed!";
        }
        
    });

    QObject::connect(login_btn, &QPushButton::clicked, [this,ip_entry,port_entry,err,layout](){
        try{
            gui.get_server().set_server_adress(ip_entry->text().toStdString())
                            .set_server_port(port_entry->text().toInt())
                            .configure_connection()
                            .receive_start();
            gui.set_login_window();
        }
        catch (std::exception &e) {
            ip_entry->setText("");
            port_entry->setText("");
            
            err->setText(e.what());
            layout->addWidget(err,5,0);
            qDebug() << "Login failed!";
        }
        
    });

    container->setStyleSheet(login_style());
    layout->addWidget(title,0,0);
    layout->addWidget(ip,1,0);  
    layout->addWidget(ip_entry,2,0);  
    layout->addWidget(port,3,0);          
    layout->addWidget(port_entry,4,0);  
    layout->addWidget(login_btn,6,0);   
    layout->addWidget(btn,6,1);  
     
    return container;
}

