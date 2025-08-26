#include "siem.hpp"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include "../gui.hpp" 
#include <QtWidgets/QGridLayout>



QGridLayout * SIEMWindow::get_window(QWidget *parent){
    QPushButton *btn = new QPushButton("OK",parent);
    QObject::connect(btn, &QPushButton::clicked, [this](){
        gui.get_server().sent("users");
    });
    QPushButton *btn2 = new QPushButton("IAR OK",parent);
    QObject::connect(btn2, &QPushButton::clicked, [this](){
    });
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(btn, 1, 0);        
    layout->addWidget(btn2, 1, 1);   
    return layout;
}