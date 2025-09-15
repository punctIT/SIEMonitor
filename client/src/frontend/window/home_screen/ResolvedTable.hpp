#pragma once 
#include <mutex>
#include <string>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>

class ResolvedTable{
    private: 
        QMainWindow *window;
        QTreeWidget *logTree; 
        int log_number;   
    public:
        ResolvedTable(QMainWindow *window);
        QWidget* get_chart();
        ResolvedTable& clear();
        ResolvedTable& pop();
        ResolvedTable& add_log(const std::string Hostname,
                           const std::string Time,
                           const std::string Source,
                           const std::string Severity,

                           const std::string Message,
                           const int top=0
                          );
    
};