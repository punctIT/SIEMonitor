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
        if(resp=="[TOP]"){
            top=1;
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
                               log.get_id(),
                               top
                            );
        // qDebug()<<resp;
    });

    layout->addWidget(text,0,0);
    layout->addWidget(incidentTable->get_chart(),1,0);
    return container;
}

void IncidentsWindow::update(){ 
    auto now=get_current_time();
    std::string cmd = std::format("GLSHS {} {} {} {} {}",type,hostname,source,datetime,now);
    gui.get_server().sent(cmd);
    datetime=now;
}

IncidentsWindow& IncidentsWindow::start_timer(){
    datetime="NONE NONE";
    top=0;
    std::string cmd = std::format("GLSHS {} {} {} {} {}",type,hostname,source,datetime,datetime);
    gui.get_server().sent(cmd);
    datetime=get_current_time();
    updateTimer->start(2000);
    return *this;
}
IncidentsWindow& IncidentsWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}