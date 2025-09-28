#pragma once

#include "../../../backend/SplitLogs.hpp"


#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QThread>
#include <QtCore/QTimer>

class MapWidget;

class GUI;

class AnalyticsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;

    MapWidget* mapWidget;
    QMainWindow* window;
    QTimer* updateTimer;
public:
    AnalyticsWindow (GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    AnalyticsWindow & start_timer();
    AnalyticsWindow & stop_timer();
    void update();
signals:
    void timer_signal();
};
