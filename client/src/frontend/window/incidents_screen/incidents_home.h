#pragma once

#include "../../../backend/SplitLogs.hpp"
#include "UpdateIncidentData.h"

#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QThread>



class GUI;

class IncidentsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QThread* updateThread = nullptr;
    UpdateIncindetData* worker = nullptr;
public:
    IncidentsWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    IncidentsWindow& create_update_thread();
    IncidentsWindow& start_update_thread();
    IncidentsWindow& stop_update_thread();
    void update();
};
