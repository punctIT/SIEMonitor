#pragma once 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <mutex>
#include <string>
class LogsTable{
    private: 
        QMainWindow *window;
        QTreeWidget *logTree ;    
    public:
        LogsTable(QMainWindow *window);
        QWidget* get_chart();
        LogsTable& update();
        LogsTable& add_log(const std::string Hostname,
                           const std::string Time,
                           const std::string Source,
                           const std::string Severity,
                           const std::string Message
                          );

        
};