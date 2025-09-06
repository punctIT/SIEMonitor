#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtCore/QTimer>  


#include "siem.h"
#include "../../gui.h"
#include "../../../backend/Utils.hpp"


QWidget * SIEMWindow::get_window(){
    infoChart = new InfoChart(window);
    logsTable = new LogsTable(window);
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);

    QLineEdit *cmd = new QLineEdit(container);
    QPushButton *run = new QPushButton("run",container);
    
    QObject::connect(run, &QPushButton::clicked, [this,cmd](){
        std::string c= cmd->text().toStdString();
        if(c =="e"){
            logsTable->pop();
        }
        else {
            gui.get_server().sent(c);
        }
        
        
       
    });
    QObject::connect(&gui.get_server(),&ServerConection::logTable,[this](QString resp){
        if(resp=="RESTART"){
            logsTable->clear();
        }
        else {
            split.set_log(resp.toStdString())
                 .split_log();
            if(!split.empty()){
                logsTable->pop().add_log(split.get_host(),
                         split.get_time(),
                         split.get_source(),
                         split.get_severity(),
                         split.get_message()
                );
                sleep(0.01);
                split.clear();
            }
        }
        
    });
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_all();
        
        for(auto l : split.get_splited_log()){
            qDebug() <<QString::fromStdString(l)<<"\n"; 
        }
         
    });
    QObject::connect(&gui.get_server(),&ServerConection::logDataNumbers,[this](QString resp){
        split.set_log(resp.mid(11).toStdString())
             .split_all();
        infoChart->set_data(split.get_id())
                  .update();
         
    });
    QObject::connect(&gui.get_server(),&ServerConection::logData,[this](QString resp){
        split.set_log(resp.toStdString())
             .split_log();
        infoChart->update_info_data(split.get_severity());
        QMetaObject::invokeMethod(this, [this]{
            infoChart->update();
        });
        
    });
    
    layout->addWidget(infoChart->get_chart(), 0, 0); 
    layout->addWidget(logsTable->get_chart(),1,0);   
    layout->addWidget(cmd, 1, 1);        
    layout->addWidget(run, 1, 2);  
    
    return container;
}
void SIEMWindow::update(){
    auto now = get_current_time();
    gui.get_server().sent(std::format("GL {} {} 10000", datetime, now))
                    .sent("LN 10");
                                
    datetime = now;  
}

SIEMWindow& SIEMWindow::start_update_thread(){
    gui.get_server().sent("GLN")
                    .sent("GLNSe Emergency")
                    .sent("GLNSe Alert")
                    .sent("GLNSe Critical")
                    .sent("GLNSe Error")
                    .sent("GLNSe Warning");
    datetime= get_current_time();
    updateThread = new QThread(this);
    worker = new UpdateSiemData(this);
    connect(worker, &UpdateSiemData::updateSIEM, this, &SIEMWindow::update);
    connect(updateThread, &QThread::started, worker, &UpdateSiemData::doWork);
    connect(updateThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(updateThread, &QThread::finished, updateThread, &QObject::deleteLater);

    worker->moveToThread(updateThread);
    updateThread->start();
    return *this;
}