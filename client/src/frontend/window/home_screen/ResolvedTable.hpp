#pragma once 
#include <mutex>
#include <string>
#include <vector>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>

class ResolvedTable{
    private: 
        QMainWindow *window;
        QTreeWidget *logTree; 
        int log_number;   
        ResolvedTable& clear();
    public:
        ResolvedTable(QMainWindow *window);
        QWidget* get_chart();
        
        ResolvedTable& pop();
        ResolvedTable& add_log(std::vector<std::string> data,const int top=0);
    
};