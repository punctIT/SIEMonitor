#pragma once 
#include <mutex>
#include <string>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>


class LocationTable{
    private: 
        QMainWindow *window;
        QListWidget *logTree; 
    public:
        LocationTable(QMainWindow *win);
        QWidget* get_widget();
        LocationTable& clear();
        LocationTable& update_data(const std::vector<std::string> data);              
    
};