#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>  


#include "siem_home.h"
#include "../../gui.h"
#include "../../../backend/Utils.hpp"
#include "../../style/style.h"

QWidget * SiemHomeWindow::get_window(){
    infoChart = new InfoChart(window);
    logsTable = new LogsTable(window);
    usersTable= new UsersTable(window);
    resolvedTable= new ResolvedTable(window);


    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);

    QGridLayout *top_layout = new QGridLayout();
    QGridLayout *down_layout = new QGridLayout();
    updateTimer = new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &SiemHomeWindow::update);
    bind_signals();
    
    welcome_msg=new QLabel("",container);
    welcome_msg->setObjectName("welcome_msg");
    
    top_layout->setColumnStretch(0,20);
    top_layout->setColumnStretch(1,60);
    top_layout->setColumnStretch(2,20);
    top_layout->addWidget(infoChart->get_data_chart(), 0, 0); 
    top_layout->addWidget(infoChart->get_chart(), 0, 1); 
    top_layout->addWidget(usersTable->get_chart(),0,2);

    down_layout->addWidget(logsTable->get_chart(),0,0);
    down_layout->addWidget(resolvedTable->get_chart(),0,1);

    layout->setRowStretch(0,20);
    layout->setRowStretch(1,35);
    layout->setRowStretch(2,45);
    layout->addWidget(welcome_msg,0,0);
    layout->addLayout(top_layout,1,0);
    layout->addLayout(down_layout,2,0);   
 
    container->setStyleSheet(siem_home_style());
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
    QObject::connect(&gui.get_server(),&ServerConection::onlineUsers,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_all();
        usersTable->set_username(username)
                    .set_users(split.get_splited_log());
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
    QObject::connect(&gui.get_server(),&ServerConection::resolvedTable,[this](QString resp){
        //qDebug()<<resp;
        split.set_log(resp.toStdString())
             .split_all();
        resolvedTable->add_log(split.get_splited_log());
           
    });
     QObject::connect(&gui.get_server(),&ServerConection::resolvedTableUpdate,[this](QString resp){
        qDebug()<<resp;
        split.set_log(resp.toStdString())
             .split_all();
        resolvedTable->add_log(split.get_splited_log(),1);
           
    });
}
void SiemHomeWindow::update(){
    auto now = get_current_time();
    gui.get_server().sent(std::format("GLND {}",now)).
                     sent(std::format("GL {} {} 10000", datetime, now)).
                     sent(std::format("GLR {} {}", datetime, now)).
                     sent("Users");

                
    datetime = now;  
}

SiemHomeWindow& SiemHomeWindow::start_update_timer(){
    auto now = get_current_time();
    gui.get_server().sent("LN 40")
                    .sent(std::format("GLND {}",now))
                    .sent("Users")
                    .sent("LNR 40");

    updateTimer->start(3000);
    welcome_msg->setText("Welcome back "+username);
    return *this;
}
SiemHomeWindow& SiemHomeWindow::stop_update_timer(){
    updateTimer->stop();
    return *this;
}
SiemHomeWindow& SiemHomeWindow::set_username(QString user){
    username=user;
    return *this;
}