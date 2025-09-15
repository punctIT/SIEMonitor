#include "OnlineUsers.hpp"



UsersTable::UsersTable(QMainWindow *win){
    window=win;
  
}

QWidget* UsersTable::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    logTree= new QListWidget(window);
    layout->addWidget(logTree,0,0);
    return container;
}

UsersTable& UsersTable::set_users(const std::vector<std::string> users){
    logTree->clear();
    for(auto i :users){
        QListWidgetItem* item= new QListWidgetItem(QString::fromStdString(i));
        qDebug()<<QString::fromStdString(i)<<" "<<username;
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