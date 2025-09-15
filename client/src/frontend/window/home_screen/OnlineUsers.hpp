#pragma once 
#include <mutex>
#include <string>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>


class UsersTable{
    private: 
        QMainWindow *window;
        QListWidget *logTree; 
        QString username;
    public:
        UsersTable(QMainWindow *win);
        QWidget* get_chart();
        UsersTable& set_users(const std::vector<std::string> users);
        UsersTable& set_username(const QString user);                
    
};