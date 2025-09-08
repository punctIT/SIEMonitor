#pragma once

#include "../../../backend/SplitLogs.hpp"

#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 




class GUI;

class IncidentsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
public:
    IncidentsWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();


};
