#include "ResolvedTable.hpp"
#include <string>
#include <format>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>


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
ResolvedTable& ResolvedTable::clear(){
     if (logTree) {
        logTree->clear();
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
    logItem->setText(0,QString::fromStdString(data[5]+" "+data[7]+" "+data[10]+" "+data[8]+" "+data[9]));
    QFont monoFont("Courier New");
    monoFont.setStyleHint(QFont::Monospace);
    logItem->setFont(0, monoFont);

    QTreeWidgetItem *msgItem = new QTreeWidgetItem(logItem);
    QWidget *msgContainer = new QWidget();
    QLabel *msgText = new QLabel(QString::fromStdString(data[11]));
    
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

