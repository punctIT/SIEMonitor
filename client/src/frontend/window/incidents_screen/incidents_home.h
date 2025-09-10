#pragma once

#include "../../../backend/SplitLogs.hpp"


#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QThread>
#include <QtCore/QTimer>


class GUI;

class IncidentsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QTimer* updateTimer;
public:
    IncidentsWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    IncidentsWindow& start_timer();
    IncidentsWindow& stop_timer();
    void update();
signals:
    void timer_signal();
};
