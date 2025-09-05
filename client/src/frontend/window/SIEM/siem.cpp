#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtCore/QTimer>  

#include "siem.h"
#include "../../gui.hpp"
#include "../../../backend/Utils.hpp"


void update_info_chart(InfoChart* infoChart,const std::string severity){
    if(severity=="Alert"){
        infoChart->count_alert();
    }
    if(severity=="Emergency"){
        infoChart->count_emergenty();
    }
    if(severity=="Error"){
        infoChart->count_error();
    }
    if(severity=="Warning"){
        infoChart->count_warning();
    }
    if(severity=="Critical"){
        infoChart->count_critial();
    }
    infoChart->count_total();
    //          .update();
}


QWidget * SIEMWindow::get_window(){
    infoChart = new InfoChart(window);
    logsTable = new LogsTable(window);

    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);

    QLineEdit *cmd = new QLineEdit(container);
    QPushButton *run = new QPushButton("run",container);


    QObject::connect(run, &QPushButton::clicked, [this,cmd](){
        std::string c= cmd->text().toStdString();
        gui.get_server().sent(c);
        
       
    });
    
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_log();
    
        for(auto l : split.get_splited_log()){
            qDebug() <<QString::fromStdString(l)<<"\n"; 
        }
         
    });

    QObject::connect(this, &SIEMWindow::infoChart_update,[this]{
        infoChart->update();
        if(!split.empty()){
             logsTable->add_log(split.get_host(),
                     split.get_time(),
                     split.get_source(),
                     split.get_severity(),
                     split.get_message()
                 );
             logsTable->add_log(split.get_host(),
                     split.get_time(),
                     split.get_source(),
                     split.get_severity(),
                     split.get_message()
                 );
             logsTable->add_log(split.get_host(),
                     split.get_time(),
                     split.get_source(),
                     split.get_severity(),
                     split.get_message()
                 );
             logsTable->add_log(split.get_host(),
                     split.get_time(),
                     split.get_source(),
                     split.get_severity(),
                     split.get_message()
                 );
             logsTable->add_log(split.get_host(),
                     split.get_time(),
                     split.get_source(),
                     split.get_severity(),
                     split.get_message()
                 );
            //split.clear();
        }
    });
    QObject::connect(&gui.get_server(),&ServerConection::logData,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_log();
        update_info_chart(infoChart,split.get_severity());
        qDebug()<<"\n"; 
    });
    layout->addWidget(infoChart->get_chart(), 0, 0); 
    layout->addWidget(logsTable->get_chart(),1,0);   
    layout->addWidget(cmd, 1, 1);        
    layout->addWidget(run, 1, 2);  
    
    
    return container;
}
SIEMWindow& SIEMWindow::update(){
    
    while(true) {
        sleep(2);  // thread worker
        datetime = get_current_time();
        QMetaObject::invokeMethod(this, [this]{
            gui.get_server().sent(std::format("GLAT {}", datetime));
            emit infoChart_update();  // emit signal în threadul principal
        }, Qt::QueuedConnection);
    }
    return *this; 
}

SIEMWindow& SIEMWindow::start_update_thread(){
     QMetaObject::invokeMethod(this, [this]{
        gui.get_server().sent("GLAT");
        datetime= get_current_time();
        emit infoChart_update();
    }, Qt::QueuedConnection);

    update_thread = std::unique_ptr<std::thread>(new std::thread(&SIEMWindow::update, this));
    update_thread->detach();
    return *this;
}