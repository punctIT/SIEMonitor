#include "incidents_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"

#include <format>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QWidget* IncidentsWindow::get_filtres_menu(){
    QWidget *container= new QWidget(window);
    QGridLayout *filters = new QGridLayout(container);

    QPushButton *refresh_btn = new QPushButton("Refresh");
    QObject::connect(refresh_btn,&QPushButton::clicked,this,&IncidentsWindow::update_types);
    QLabel *host_lb= new QLabel("Hostname");
    hostname_box= new QComboBox(window);
  

    QLabel *severity_lb= new QLabel("Severity");
    type_box = new QComboBox(window);
    type_box->addItems({"ALL","HIGH","MEDIUM","LOW"});
   
    
    QLabel *search_bl = new QLabel("Search");
    search_entry= new QLineEdit();

    filters->addWidget(refresh_btn,0,0);
    filters->addWidget(severity_lb,0,1);
    filters->addWidget(type_box,0,2);
    filters->addWidget(host_lb,0,3);
    filters->addWidget(hostname_box,0,4);
    filters->addWidget(search_bl,0,5);
    filters->addWidget(search_entry,0,6);

    return container;
}
QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    
    QLabel *text = new QLabel("Incidents");
    incidentTable= new IncidentTable(this,window);

    updateTimer=new QTimer(window);
    
    layout->addWidget(text,0,0);
    layout->addWidget(get_filtres_menu(),1,0);
    layout->addWidget(incidentTable->get_chart(),2,0);
    bind_signals();
    return container;
}
void IncidentsWindow::bind_signals(){
    QObject::connect(hostname_box,&QComboBox::currentTextChanged,this,&IncidentsWindow::update_types);
    connect(updateTimer, &QTimer::timeout, this, &IncidentsWindow::update);
    QObject::connect(type_box,&QComboBox::currentTextChanged,this,&IncidentsWindow::update_types);
    QObject::connect(search_entry,&QLineEdit::textChanged,this,[this](){
        search=search_entry->text().toStdString();
        if(search.empty()){
            search="NONE";
        }
        update_types();
    });

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
                               log.get_date(),
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
    std::string cmd = std::format("GLSHS {} {} {} {} {} {}",type, hostname, source,datetime,datetime,search);
    gui.get_server().sent(cmd);
   
}
void IncidentsWindow::update(){ 
    auto now=get_current_time();
    std::string cmd = std::format("GLSHS {} {} {} {} {} {}",type,hostname,source,datetime,now,search);
    // if(datetime!="NONE NONE")
    //     gui.get_server().sent(cmd);
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