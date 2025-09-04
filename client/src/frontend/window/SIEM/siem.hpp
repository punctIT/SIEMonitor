
#pragma once
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <thread>
#include <memory>
#include "InfoChart.hpp"
#include <string>

class GUI;

class SIEMWindow{
private:
    GUI& gui; 
    std::unique_ptr<std::thread> update_thread;
    InfoChart* infoChart;
    SIEMWindow& update();
    std::string datetime;
public:
    SIEMWindow(GUI &srv) : gui(srv){}
    QWidget* get_window();
    SIEMWindow& start_update_thread();

};
