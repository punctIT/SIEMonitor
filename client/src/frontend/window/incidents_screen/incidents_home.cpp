#include "incidents_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"


#include <format>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>


QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QGridLayout *filters = new QGridLayout(container);

    QLabel *text = new QLabel("Incidents");
    incidentTable= new IncidentTable(this,window);
    
    QLabel *host_lb= new QLabel("Hostname");
    hostname_box= new QComboBox(window);
    QObject::connect(hostname_box,&QComboBox::currentTextChanged,this,&IncidentsWindow::update_types);

    QLabel *severity_lb= new QLabel("Severity");
    type_box = new QComboBox(window);
    type_box->addItems({"ALL","HIGH","MEDIUM","LOW"});
    QObject::connect(type_box,&QComboBox::currentTextChanged,this,&IncidentsWindow::update_types);
    
    filters->addWidget(severity_lb,0,0);
    filters->addWidget(type_box,0,1);
    filters->addWidget(host_lb,0,2);
    filters->addWidget(hostname_box,0,3);


    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &IncidentsWindow::update);
    bind_signals();

    layout->addWidget(text,0,0);
    layout->addLayout(filters,1,0);
    layout->addWidget(incidentTable->get_chart(),2,0);
    return container;
}
void IncidentsWindow::bind_signals(){
    QObject::connect(&gui.get_server(),&ServerConection::HostsEnum,[this](QString resp){
        hostname_box->clear();
        hostname_box->addItem("All");
        SplitLog log;
        log.set_log(resp.toStdString())
           .split_all();
        for(auto host : log.get_splited_log()){
            hostname_box->addItem(QString::fromStdString(host));
        }
        
     });

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
}
void IncidentsWindow::update_types(){
   
    type=type_box->currentText().toStdString();
    hostname="NONE";
    if(hostname_box->currentText().toStdString()!="All"){
        hostname=hostname_box->currentText().toStdString();
        if(hostname.empty()){
            hostname="NONE";
        }
    }
    
    datetime="NONE NONE";
    top=0;
    std::string cmd = std::format("GLSHS {} {} {} {} {}",type, hostname, source,datetime,datetime);
    gui.get_server().sent(cmd);
   
}
void IncidentsWindow::update(){ 
    auto now=get_current_time();
    std::string cmd = std::format("GLSHS {} {} {} {} {}",type,hostname,source,datetime,now);
    if(datetime!="NONE NONE")
        gui.get_server().sent(cmd);
    datetime=now;

}

IncidentsWindow& IncidentsWindow::start_timer(){
    datetime="NONE NONE";
    top=0;
    std::string cmd = std::format("GLSHS {} {} {} {} {}",type, hostname, source,datetime,datetime);
    gui.get_server().sent(cmd).sent("HOSTS");
    datetime=get_current_time();
    updateTimer->start(2000);
    return *this;
}
IncidentsWindow& IncidentsWindow::stop_timer(){
    updateTimer->stop();
    return *this;
}
GUI& IncidentsWindow::get_gui(){
    return gui;
}