#pragma once 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <mutex>
#include <string>
class LogsTable{
    private: 
        QTreeWidget *logTree ;    
    public:
        LogsTable();
        QWidget* get_chart();
        LogsTable& update();
        LogsTable& add_log(const std::string Hostname,
                           const std::string Time,
                           const std::string Source,
                           const std::string Severity,
                           const std::string Message
                             );

        
};