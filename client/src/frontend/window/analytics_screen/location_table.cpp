#include "location_table.hpp"

#include <format>
#include <string>
LocationTable::LocationTable(QMainWindow *win){
    window=win; 
}
static std::string indent_text(std::string text,int len){
     if(text.size()>len){
        text.erase(len-3,text.size());
        text+="...";
    }
    else {
        text.resize(len, ' ');
    }
    return text;
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
    if(data.size()<6){
        return *this;
    }
    const std::string text=std::format("{} {} {} {} {} {}",
        indent_text(data[0],12),
        indent_text(data[1],4),
        indent_text(data[2],11),
        indent_text(data[3],11),
        indent_text(data[4],14),
        indent_text(data[5],15)
    );
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(text));
    QFont monoFont("Courier New");
    monoFont.setStyleHint(QFont::Monospace);
    item->setFont(monoFont);
    logTree->insertItem(0,item);
    
    return *this;
}
