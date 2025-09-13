#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>  


#include "siem_home.h"
#include "../../gui.h"
#include "../../../backend/Utils.hpp"


QWidget * SiemHomeWindow::get_window(){
    infoChart = new InfoChart(window);
    logsTable = new LogsTable(window);
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QGridLayout *top_layout = new QGridLayout(container);
    updateTimer = new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &SiemHomeWindow::update);
    bind_signals();
    
    
    top_layout->addWidget(infoChart->get_data_chart(), 0, 0); 
    top_layout->addWidget(infoChart->get_chart(), 0, 1); 
    layout->addLayout(top_layout,0,0);
    layout->addWidget(logsTable->get_chart(),1,0);   
 
    
    return container;
}
void SiemHomeWindow::bind_signals(){
    QObject::connect(&gui.get_server(),&ServerConection::logTable,[this](QString resp){
        if(resp=="RESTART"){
            logsTable->clear();
        }
        else {
            split.set_log(resp.toStdString())
                 .split_log();
            if(!split.empty()){
                logsTable->add_log(split.get_host(),
                         split.get_time(),
                         split.get_source(),
                         split.get_severity(),
                         split.get_message()
                );
                split.clear();
            }
        }
        
    });
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_all();
        
        for(auto l : split.get_splited_log()){
            qDebug() <<QString::fromStdString(l);
        }
         
    });
    QObject::connect(&gui.get_server(),&ServerConection::logDataNumbers,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_all();
        infoChart->set_data(split.get_splited_log())
                  .update();
         
    });
    QObject::connect(&gui.get_server(),&ServerConection::logData,[this](QString resp){
        //qDebug()<<resp;
        split.set_log(resp.toStdString())
             .split_log();
        if(!split.empty()){
            logsTable->pop().
                    add_log(split.get_host(),
                           split.get_time(),
                           split.get_source(),
                           split.get_severity(),
                           split.get_message(),
                           1
            );
            split.clear();
        }
           
    });
}
void SiemHomeWindow::update(){
    auto now = get_current_time();
    gui.get_server().sent(std::format("GLND {}",now)).
                     sent(std::format("GL {} {} 10000", datetime, now));
                
    datetime = now;  
}

SiemHomeWindow& SiemHomeWindow::start_update_timer(){
    auto now = get_current_time();
    gui.get_server().sent("LN 15")
                    .sent(std::format("GLND {}",now));
    updateTimer->start(3000);
    return *this;
}
SiemHomeWindow& SiemHomeWindow::stop_update_timer(){
    updateTimer->stop();
    return *this;
}