
#pragma once

#include "InfoChart.hpp"
#include "LogsTable.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <thread>
#include <memory>
#include <string>
#include "UpdateSiemData.h"
#include "../../../backend/SplitLogs.hpp"


class GUI;

class SIEMWindow : public QObject {
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
    SIEMWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    SIEMWindow& start_update_thread(); 

private slots:
    void update();

};
