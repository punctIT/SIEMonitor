#pragma once 
#include <mutex>
#include <string>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>

class IncidentsWindow;

class IncidentTable{
    private: 
        QMainWindow *window;
        QListWidget *logTree;
        IncidentsWindow* incidentWindow; 
        int log_number;   
    public:
        IncidentTable(IncidentsWindow* incWindow,QMainWindow *win);
        QWidget* get_chart();
        IncidentTable& update();
        IncidentTable& clear();
        IncidentTable& pop();
        IncidentTable& add_log(const std::string Hostname,
                           const std::string Time,
                           const std::string Source,
                           const std::string Severity,
                           const std::string Message,
                           const int id,
                           const int top
                          );
    
};