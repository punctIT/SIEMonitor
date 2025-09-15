#pragma once

#include "../../../backend/SplitLogs.hpp"
#include "InfoChart.hpp"
#include "LogsTable.hpp"
#include "OnlineUsers.hpp"
#include "ResolvedTable.hpp"
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
    UsersTable* usersTable;
    ResolvedTable* resolvedTable;
    
    QLabel* welcome_msg;
    SplitLog split;
    std::string datetime;
    QString username;
    int res=0;
public:
    SiemHomeWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    SiemHomeWindow& start_update_timer();  
    SiemHomeWindow& stop_update_timer();
    SiemHomeWindow& set_username(QString user);
    void bind_signals();

private slots:
    void update();

};
