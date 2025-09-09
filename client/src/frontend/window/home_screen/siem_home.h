#pragma once

#include "../../../backend/SplitLogs.hpp"
#include "UpdateSiemData.h"
#include "InfoChart.hpp"
#include "LogsTable.hpp"

#include <string>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 




class GUI;

class SiemHomeWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QThread* updateThread = nullptr;
    UpdateSiemData* worker = nullptr;

    InfoChart* infoChart;
    LogsTable* logsTable;
    
    SplitLog split;
    std::string datetime;
public:
    SiemHomeWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    SiemHomeWindow& create_update_thread();  
    SiemHomeWindow& stop_update_thread();
private slots:
    void update();

};
