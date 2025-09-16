#include "incidents_table.hpp"
#include "incidents_home.h"
#include "../../gui.h"

#include <string>
#include <format>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>




std::string get_spaced(std::string name,int len){
    if(name.size()>len){
        name.erase(len-3,name.size());
        name+="...";
    }
    else {
        name.resize(len, ' ');
    }
    return name;
}


IncidentTable::IncidentTable(IncidentsWindow *inc,QMainWindow *win){
    incidentWindow=inc;
    window=win;
}
void IncidentTable::bind_signals(){
    QObject::connect(logTree, &QListWidget::itemDoubleClicked,
                     [&](QListWidgetItem *item){
        int nr = item->data(Qt::UserRole).toInt();
        QString msg = item->data(Qt::UserRole+1).toString();
        qDebug()<<nr<<" "<<msg;
    });
    QObject::connect(logTree, &QListWidget::itemChanged, [this](QListWidgetItem *item){
        if(item->checkState() == Qt::Checked) {
            check_count+=1;
            if(check_count>0){
                save_btn->show();
            }
        } 
        else {
            check_count-=1;
            if(check_count==0){
                save_btn->hide();
            }
        }
    });
    QObject::connect(save_btn,&QPushButton::clicked,[this](){
        check_count=0;
        for (int i = logTree->count() - 1; i >= 0; --i) {
            QListWidgetItem* item = logTree->item(i);
            if(item->checkState() == Qt::Checked) {
                std::string id = item->data(Qt::UserRole).toString().toStdString();
                incidentWindow->get_gui().get_server().sent(std::format("UpRe {} {}",id,incidentWindow->get_username().toStdString()));
                delete logTree->takeItem(i);
            }
        }
        if(check_count==0){
            save_btn->hide();
        }
    });
    
}
QWidget* IncidentTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    logTree= new QListWidget(container);

    logTree->setStyleSheet(
        "QListWidget::item { "
        "padding: 5px 5px 5px; "  
        "}"
    );
    
    std::string text = std::format("{}{} {} {} {} {} {}",
                                    get_spaced("Resolved",12),
                                    get_spaced("Hostname",31),
                                    get_spaced("Time",36),
                                    get_spaced("Date",33),
                                    get_spaced("Source",34),
                                    get_spaced("Severity",36),
                                    get_spaced("Message",50)
                                );
    QLabel *head=new QLabel(QString::fromStdString(text),container);
    head->setStyleSheet(
        "QLabel { padding: 5px 5px; }"
    );
    save_btn = new QPushButton("Save",container);

    layout->addWidget(head,0,0);
    layout->addWidget(logTree,1,0);
    layout->addWidget(save_btn,2,0);
    save_btn->hide();
    bind_signals();
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
                              const std::string Date,
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

    std::string text = std::format("    {} {} {} {} {} {}",get_spaced(Hostname,20),
                                                    get_spaced(Time,20),
                                                    get_spaced(Date,20),
                                                    get_spaced(Source,20),
                                                    get_spaced(Severity,20),
                                                    get_spaced(Message,50)
                                                );

    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(text));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);  
    item->setCheckState(Qt::Unchecked);                      
    item->setData(Qt::UserRole,id);
    item->setData(Qt::UserRole+1,QString::fromStdString(Message));

    QPixmap spacer(20, 10);
    if(Severity=="Alert"||Severity=="Emergency"||Severity=="Critical"){
        spacer.fill(Qt::red);
    }
    else if(Severity=="Warning"||Severity=="Error"){
        spacer.fill(Qt::yellow);
    }
    else {
        spacer.fill(Qt::green);
    }
   
    item->setIcon(QIcon(spacer));

    QFont monoFont("Courier New");
    monoFont.setStyleHint(QFont::Monospace);
    item->setFont(monoFont);

    if(top==1)
        logTree->insertItem(0,item);
    else {
        logTree->addItem(item);   
    }
    return *this;
}
