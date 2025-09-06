#include "LogsTable.hpp"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <string>
#include <format>

QString get_spaced_string(std::string name,int len){
    if(name.size()>len){
        name.erase(len-3,name.size());
        name+="...";
    }
    else {
        name.resize(len, ' ');
    }
    return QString::fromStdString(name);
}


LogsTable::LogsTable(QMainWindow *win){
    window=win;
    log_number=0;
}
QWidget* LogsTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    logTree= new QTreeWidget(container);
    logTree->setColumnCount(1);
    logTree->resizeColumnToContents(1);
    logTree->setHeaderLabels({get_spaced_string("      Hostname",37)+
                              get_spaced_string("Time",40)+
                              get_spaced_string("Source",33)+
                              get_spaced_string("Severity",20)
                             });
    

    QPushButton *btn = new QPushButton("new",container);
    QObject::connect(btn, &QPushButton::clicked, [this](){
        add_log("1","2","3","4","5");
    });

    layout->addWidget(logTree,0,0);
    layout->addWidget(btn,0,1);
    return container;
}
LogsTable& LogsTable::clear(){
     if (logTree) {
        logTree->clear();
    }
    return *this;
}
LogsTable& LogsTable::pop(){
    if (!logTree || log_number<15) return *this;
    
    int itemCount = logTree->topLevelItemCount();
    if (itemCount > 0) {
        QTreeWidgetItem* lastItem = logTree->topLevelItem(itemCount - 1);
        delete lastItem;
    }
    return *this;
}

LogsTable& LogsTable::add_log(const std::string Hostname,
                              const std::string Time,
                              const std::string Source,
                              const std::string Severity,
                              const std::string Message,
                              const int top
                             ){

    QTreeWidgetItem *logItem = new QTreeWidgetItem();
    logItem->setText(0, get_spaced_string(Hostname,21)+
                        get_spaced_string(Time,23)+
                        get_spaced_string(Source,20)+
                        get_spaced_string(Severity,20));
    
    QFont monoFont("Courier New");
    monoFont.setStyleHint(QFont::Monospace);
    logItem->setFont(0, monoFont);

    QTreeWidgetItem *msgItem = new QTreeWidgetItem(logItem);
    QWidget *msgContainer = new QWidget();
    QLabel *msgText = new QLabel(QString::fromStdString(Message));
    msgText->setWordWrap(true); 
    logTree->setItemWidget(msgItem, 0, msgText);
    if(top != 0){
        logTree->insertTopLevelItem(0, logItem); 
    } else {
        logTree->addTopLevelItem(logItem);
    }
    log_number+=1;
    return *this;
}

LogsTable& LogsTable::update(){
    return *this;
}