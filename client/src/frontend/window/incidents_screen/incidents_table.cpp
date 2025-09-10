#include "incidents_table.hpp"
#include <string>
#include <format>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
 



IncidentTable::IncidentTable(QMainWindow *win){
   
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
    QObject::connect(logTree, &QListWidget::itemChanged, [&](QListWidgetItem *item){
        if(item->checkState() == Qt::Checked) {
            qDebug() << "Bifat:" << item->text();
        } else {
            qDebug() << "Debifat:" << item->text();
        }
    });

    QListWidgetItem *item = new QListWidgetItem("primu");                    
    logTree->addItem(item);

    QPushButton *btn = new QPushButton("add");
    QObject::connect(btn,&QPushButton::clicked,[this](){
        add_log("","","","","");
    });
    layout->addWidget(btn,0,1);
    layout->addWidget(logTree,0,0);
    return container;
}
IncidentTable& IncidentTable::clear(){
    logTree->clear();
    QListWidgetItem *item = new QListWidgetItem("primu");                    
    logTree->addItem(item);
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
                              const int id
                             ){
                            
    std::string text = std::format("{} {} {} {}",Hostname,Time,Source,Severity);
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(text));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);  
    item->setCheckState(Qt::Unchecked);                      
    item->setData(Qt::UserRole,id);
    item->setData(Qt::UserRole+1,QString::fromStdString(Message));
    logTree->insertItem(1,item);
    return *this;
}
