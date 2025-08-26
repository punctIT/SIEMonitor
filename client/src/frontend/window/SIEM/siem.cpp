#include "siem.hpp"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include "../../gui.hpp"


QWidget * SIEMWindow::get_window(){
    QWidget *container= new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    QPushButton *btn = new QPushButton("OK",container);
    QObject::connect(btn, &QPushButton::clicked, [this](){
        gui.get_server().sent("users");
    });
    QPushButton *btn2 = new QPushButton("IAR OK",container);
    
    QObject::connect(btn2, &QPushButton::clicked, [this](){
        
    });
    
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        qDebug() <<resp;     
    });

    layout->addWidget(btn, 1, 0);        
    layout->addWidget(btn2, 1, 1);   
    return container;
}