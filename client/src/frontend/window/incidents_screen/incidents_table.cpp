#include "incidents_table.hpp"
#include "incidents_home.h"
#include "../../gui.h"
#include <string>
#include <format>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
 



IncidentTable::IncidentTable(IncidentsWindow *inc,QMainWindow *win){
    incidentWindow=inc;
    window=win;
}

QWidget* IncidentTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    logTree= new QListWidget(container);
    QObject::connect(logTree, &QListWidget::itemDoubleClicked,
                     [&](QListWidgetItem *item){
        int nr = item->data(Qt::UserRole).toInt();
        QString msg = item->data(Qt::UserRole+1).toString();
        qDebug()<<nr<<" "<<msg;
    });
    QObject::connect(logTree, &QListWidget::itemChanged, [this](QListWidgetItem *item){
        if(item->checkState() == Qt::Checked) {
            std::string id = item->data(Qt::UserRole).toString().toStdString();
            incidentWindow->get_gui().get_server().sent(std::format("UpRe {} {}",id,1));
            delete logTree->takeItem(logTree->row(item));
        } 
    });
    layout->addWidget(logTree,0,0);
    return container;
}
IncidentTable& IncidentTable::clear(){
    logTree->clear();                   
    log_number=0;
    return *this;
}
IncidentTable& IncidentTable::pop(){
   if ( logTree &&  logTree->count() > 1) {
        delete  logTree->takeItem( logTree->count() - 1);  
    }
    return *this;
}
IncidentTable& IncidentTable::add_log(const std::string Hostname,
                              const std::string Time,
                              const std::string Source,
                              const std::string Severity,
                              const std::string Message,
                              const int id,
                              const int top
                             ){
    if(log_number>150){
        pop();
    }
    log_number+=1;
    std::string text = std::format("{} {} {} {}",Hostname,Time,Source,Severity);
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(text));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);  
    item->setCheckState(Qt::Unchecked);                      
    item->setData(Qt::UserRole,id);
    item->setData(Qt::UserRole+1,QString::fromStdString(Message));
    if(top==1)
        logTree->insertItem(0,item);
    else {
        logTree->addItem(item);   
    }
    return *this;
}
