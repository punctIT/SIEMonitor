#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

#include "siem.hpp"
#include "../../gui.hpp"
#include "../../../backend/SplitLogs.hpp"
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
    infoChart = new InfoChart();

    QWidget *container= new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    QLineEdit *cmd = new QLineEdit(container);
    QPushButton *run = new QPushButton("run",container);

    QObject::connect(run, &QPushButton::clicked, [this,cmd](){
        std::string c= cmd->text().toStdString();
        gui.get_server().sent(c);
        
       
    });
    
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        SplitLog split;
        split.set_log(resp.toStdString())
             .split_log();
    
        for(auto l : split.get_splited_log()){
            qDebug() <<QString::fromStdString(l)<<"\n"; 
        }
         
    });

    QObject::connect(&gui.get_server(),&ServerConection::logData,[this](QString resp){
        SplitLog split;
        split.set_log(resp.toStdString())
             .split_log();
        update_info_chart(infoChart,split.get_severity());
        //qDebug()<<"ok\n"; 
    });
    layout->addWidget(infoChart->get_chart(), 0, 0);    
    layout->addWidget(cmd, 1, 0);        
    layout->addWidget(run, 1, 1);  
    
    
    return container;
}
SIEMWindow& SIEMWindow::update(){
    gui.get_server().sent("GLAT");
    infoChart->update();
    datetime= get_current_time();
    while(true){
        sleep(2);
        qDebug()<<QString::fromStdString(datetime)<<"\n";
        gui.get_server().sent(std::format("GLAT {}",datetime));
        infoChart->update();
        datetime= get_current_time();
    }  
}
SIEMWindow& SIEMWindow::start_update_thread(){
    update_thread = std::unique_ptr<std::thread>(new std::thread(&SIEMWindow::update, this));
    update_thread->detach();
    return *this;
}