#pragma once
#include <string>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtWidgets/QStackedWidget>


class SiemHomeWindow;
class IncidentsWindow;
class GUI;

class SIEMWindow{
private:
    GUI& gui;
    QMainWindow* window;
    QStackedWidget* stack_window;
    SiemHomeWindow* homeWindow;
    IncidentsWindow *incidentsWindow;
public:
    SIEMWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    void start_home_thread();
};
