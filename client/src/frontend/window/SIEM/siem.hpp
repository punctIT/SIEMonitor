
#pragma once

#include "InfoChart.hpp"
#include "LogsTable.hpp"

#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <thread>
#include <memory>
#include <string>



class GUI;

class SIEMWindow{
private:
    GUI& gui; 
    std::unique_ptr<std::thread> update_thread;
    InfoChart* infoChart;
    LogsTable* logsTable;

    SIEMWindow& update();
    std::string datetime;
public:
    SIEMWindow(GUI &srv) : gui(srv){}
    QWidget* get_window();
    SIEMWindow& start_update_thread();

};
