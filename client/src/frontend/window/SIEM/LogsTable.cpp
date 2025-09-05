#include "LogsTable.hpp"
#include <QtWidgets/QPushButton>
#include <string>




LogsTable::LogsTable(){

}
QWidget* LogsTable::get_chart(){
    QWidget *container = new QWidget();
    QGridLayout* layout = new QGridLayout(container);
    logTree= new QTreeWidget(container);
    logTree->setColumnCount(5);
    logTree->setHeaderLabels({"Hostname","Time", "Source","severity", "message"});
    

    QPushButton *btn = new QPushButton("new",container);
    QObject::connect(btn, &QPushButton::clicked, [this](){
        add_log("1","2","3","4","5");
    });

    layout->addWidget(logTree,0,0);
    layout->addWidget(btn,0,1);
    return container;
}
LogsTable& LogsTable::add_log(const std::string Hostname,
                              const std::string Time,
                              const std::string Source,
                              const std::string Severity,
                              const std::string Message
                             ){
    QTreeWidgetItem *logItem = new QTreeWidgetItem(logTree);
    logItem->setText(0, QString::fromStdString(Hostname));
    logItem->setText(1, QString::fromStdString(Time));
    logItem->setText(2, QString::fromStdString(Source));
    logItem->setText(3, QString::fromStdString(Severity));
    logItem->setText(4, QString::fromStdString(Message));

    logTree->scrollToItem(logItem);
    return *this;
}
LogsTable& LogsTable::update(){
    return *this;
}