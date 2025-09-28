#include "search_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* SearchWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Search");
    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &SearchWindow::update);
    
    layout->addWidget(text);


    // QObject::connect(&gui.get_server(),&ServerConection::IncidentsResponse,[this](QString resp){
    //     qDebug()<<resp;
    // });

    return container;
}

void SearchWindow::update(){
    //gui.get_server().sent("GLSHS ALL NONE NONE");
    qDebug()<<"search";
}

SearchWindow& SearchWindow::start_timer(){
    
    updateTimer->start(2000);
    return *this;
}
SearchWindow& SearchWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}