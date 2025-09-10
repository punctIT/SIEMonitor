#include "incidents_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Incidents");
    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &IncidentsWindow::update);
    
    layout->addWidget(text);


    QObject::connect(&gui.get_server(),&ServerConection::IncidentsResponse,[this](QString resp){
        qDebug()<<resp;
    });

    return container;
}

void IncidentsWindow::update(){
    gui.get_server().sent("GLSHS ALL NONE NONE");
}

IncidentsWindow& IncidentsWindow::start_timer(){
    
    updateTimer->start(2000);
    return *this;
}
IncidentsWindow& IncidentsWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}