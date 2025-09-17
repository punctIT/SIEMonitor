#include "OnlineUsers.hpp"



UsersTable::UsersTable(QMainWindow *win){
    window=win;
  
}

QWidget* UsersTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    logTree= new QListWidget(window);
    QLabel *title_lg=new QLabel("Online users:");
    layout->setRowStretch(0,1);
    layout->setRowStretch(0,99);
    layout->addWidget(title_lg,0,0);
    layout->addWidget(logTree,1,0);
    title_lg->setObjectName("data_msg");
    container->setObjectName("data");
    return container;
}

UsersTable& UsersTable::set_users(const std::vector<std::string> users){
    logTree->clear();
    for(auto i :users){
        QListWidgetItem* item= new QListWidgetItem(QString::fromStdString(i));
        //qDebug()<<QString::fromStdString(i)<<" "<<username;
        if(i==username.toStdString()){
           QFont font = item->font();  
            font.setBold(true);     
            item->setFont(font);  
        }
        logTree->addItem(item);
    }
    return *this;
}
UsersTable& UsersTable::set_username(const QString user){
      username=user;
      return *this;
}