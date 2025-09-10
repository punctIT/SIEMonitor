#include "incidents_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"


#include <format>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Incidents");
    incidentTable= new IncidentTable(window);

    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &IncidentsWindow::update);
    
    


    QObject::connect(&gui.get_server(),&ServerConection::IncidentsResponseTable,[this](QString resp){
        if(resp=="[RESTART]"){
            incidentTable->clear();
            return;
        }
        SplitLog log;
        log.set_log(resp.toStdString())
           .split_log();
        incidentTable->add_log(log.get_host(),
                               log.get_time(),
                               log.get_source(),
                               log.get_severity(),
                               log.get_message(),
                               log.get_id()
                            );
    });

    layout->addWidget(text,0,0);
    layout->addWidget(incidentTable->get_chart(),1,0);
    return container;
}

void IncidentsWindow::update(){
    datetime=get_current_time();
    std::string cmd = std::format("GLSHS {} {} {} {}",type,hostname,source,datetime);
    gui.get_server().sent(cmd);
}

IncidentsWindow& IncidentsWindow::start_timer(){
    datetime="NONE NONE";
    std::string cmd = std::format("GLSHS {} {} {} {}",type,hostname,source,datetime);
    gui.get_server().sent(cmd);
    updateTimer->start(2000);
    return *this;
}
IncidentsWindow& IncidentsWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}