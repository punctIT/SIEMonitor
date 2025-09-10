#pragma once 
#include <mutex>
#include <string>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>

class IncidentTable{
    private: 
        QMainWindow *window;
        QListWidget *logTree ; 
        int log_number;   
    public:
        IncidentTable(QMainWindow *window);
        QWidget* get_chart();
        IncidentTable& update();
        IncidentTable& clear();
        IncidentTable& pop();
        IncidentTable& add_log(const std::string Hostname,
                           const std::string Time,
                           const std::string Source,
                           const std::string Severity,
                           const std::string Message,
                           const int top=0
                          );
    
};