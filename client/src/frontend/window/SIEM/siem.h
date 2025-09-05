
#pragma once

#include "InfoChart.hpp"
#include "LogsTable.hpp"

#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <thread>
#include <memory>
#include <string>

#include "../../../backend/SplitLogs.hpp"


class GUI;

class SIEMWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui; 
    std::unique_ptr<std::thread> update_thread;
    InfoChart* infoChart;
    LogsTable* logsTable;
    
    SplitLog split;
    SIEMWindow& update();
    std::string datetime;
public:
    SIEMWindow(GUI &srv) : gui(srv){}
    QWidget* get_window();
    SIEMWindow& start_update_thread();
signals:
    void infoChart_update(); 

};
