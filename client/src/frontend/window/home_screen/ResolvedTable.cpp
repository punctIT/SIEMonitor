#include "ResolvedTable.hpp"
#include <string>
#include <format>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>

QString indent_text(std::string text,int len){
     if(text.size()>len){
        text.erase(len-3,text.size());
        text+="...";
    }
    else {
        text.resize(len, ' ');
    }
    return QString::fromStdString(text);
}

ResolvedTable::ResolvedTable(QMainWindow *win){
    window=win;
    log_number=0;
}

QWidget* ResolvedTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    logTree= new QTreeWidget(container);
    logTree->setColumnCount(1);
    logTree->resizeColumnToContents(1);
   
    logTree->setStyleSheet(
        "QTreeWidget::item { "
        "padding: 5px 5px 5px; " 
        "font-weight: bold;"
        "font-size: 15px;"
        "}"
    );
    
    layout->addWidget(logTree,0,0);
    return container;
}
ResolvedTable& ResolvedTable::clear() {
    if (logTree) {
        while (logTree->topLevelItemCount() > 0) {
            QTreeWidgetItem* item = logTree->takeTopLevelItem(0); 
            delete item; 
        }
    }
    return *this;
}

ResolvedTable& ResolvedTable::pop(){
    if (!logTree || log_number<40) return *this;
    
    int itemCount = logTree->topLevelItemCount();
    if (itemCount > 0) {
        QTreeWidgetItem* lastItem = logTree->topLevelItem(itemCount - 1);
        delete lastItem;
    }
    return *this;
}

ResolvedTable& ResolvedTable::add_log(std::vector<std::string> data,const int top){
        
    if(data[0]=="RESTART"){
        clear();
        return *this;
    }
    if(data.size()<12){
        return *this;
    }
    QTreeWidgetItem *logItem = new QTreeWidgetItem();
    //5 host
    //7 severity
    //8 9 time date resolved
    //10 -who resolved
    //11 message
    logItem->setText(0,indent_text(data[5],30)+indent_text(data[7],15)+indent_text(data[10],20)+indent_text(data[8],10)+indent_text(data[9],10));
    QFont monoFont("Courier New");
    monoFont.setStyleHint(QFont::Monospace);
    logItem->setFont(0, monoFont);

    QTreeWidgetItem *msgItem = new QTreeWidgetItem(logItem);
    QWidget *msgContainer = new QWidget();
    std::string msg;
    for(int i=11;i<data.size();++i){
        msg=msg+" "+data[i];
    }
    QLabel *msgText = new QLabel(QString::fromStdString(msg));
    
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

