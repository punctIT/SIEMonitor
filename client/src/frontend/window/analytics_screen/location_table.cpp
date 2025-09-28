#include "location_table.hpp"

#include <format>

LocationTable::LocationTable(QMainWindow *win){
    window=win;
  
}

QWidget* LocationTable::get_widget(){
    QWidget *container = new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    logTree= new QListWidget(window);
    QLabel *title_lg=new QLabel("Location ip data:");
    layout->setRowStretch(0,1);
    layout->setRowStretch(0,99);
    logTree->setMinimumHeight(1000);
    layout->addWidget(title_lg,0,0);
    layout->addWidget(logTree,1,0);

    title_lg->setObjectName("data_msg");
    container->setObjectName("data");
    container->setMinimumWidth(600);
    return container;
}

LocationTable& LocationTable::clear(){
    logTree->clear();
    return *this;
}

LocationTable& LocationTable::update_data(const std::vector<std::string> data){
    std::string text="";
    for(auto i : data){
        text=std::format("{} {}",text,i);
    }
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(text));
    logTree->insertItem(0,item);
    
    return *this;
}
