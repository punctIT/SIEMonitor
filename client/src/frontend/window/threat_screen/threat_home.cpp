#include "threat_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* ThreatWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Threat");
    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &ThreatWindow::update);
    
    layout->addWidget(text);


    // QObject::connect(&gui.get_server(),&ServerConection::IncidentsResponse,[this](QString resp){
    //     qDebug()<<resp;
    // });

    return container;
}

void ThreatWindow::update(){
    //gui.get_server().sent("GLSHS ALL NONE NONE");
    qDebug()<<"threat";
}

ThreatWindow& ThreatWindow::start_timer(){
    
    updateTimer->start(2000);
    return *this;
}
ThreatWindow& ThreatWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}