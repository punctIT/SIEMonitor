#pragma once

#include "../../../backend/SplitLogs.hpp"


#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include "incidents_table.hpp"


class GUI;

class IncidentsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QTimer* updateTimer;
    IncidentTable* incidentTable;


    std::string datetime;
    std::string hostname;
    std::string type;
    std::string source;
    int top;
public:
    IncidentsWindow(GUI &srv,QMainWindow* win) :
                    gui(srv) , window(win),
                    datetime("NONE NONE"),hostname("NONE"),
                    type("ALL"),source("NONE"){}
    QWidget* get_window();
    IncidentsWindow& start_timer();
    IncidentsWindow& stop_timer();
    void update();
};
