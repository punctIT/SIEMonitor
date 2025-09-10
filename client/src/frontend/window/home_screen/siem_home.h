#pragma once

#include "../../../backend/SplitLogs.hpp"
#include "InfoChart.hpp"
#include "LogsTable.hpp"

#include <string>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QTimer>



class GUI;

class SiemHomeWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QTimer* updateTimer;

    InfoChart* infoChart;
    LogsTable* logsTable;
    
    SplitLog split;
    std::string datetime;
public:
    SiemHomeWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    SiemHomeWindow& start_update_timer();  
    SiemHomeWindow& stop_update_timer();
private slots:
    void update();

};
