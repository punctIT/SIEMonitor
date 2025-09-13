#pragma once

#include "../../../backend/SplitLogs.hpp"


#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCore/QObject> 
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>


#include "incidents_table.hpp"
#include "Incidents_chart.hpp"

class GUI;

class IncidentsWindow : public QObject {
    Q_OBJECT
private:
    GUI& gui;
    QMainWindow* window;
    QTimer* updateTimer;
    IncidentTable* incidentTable;
    IncidentsChart* incidentsChart;

    QComboBox *type_box;
    QComboBox *hostname_box;
    QLineEdit *search_entry;

    std::string datetime="NONE NONE";
    std::string hostname="NONE";
    std::string type="ALL";
    std::string source="NONE";
    std::string search="NONE";
    int top;

    void bind_signals();
    QWidget* get_filtres_menu();
public:
    IncidentsWindow(GUI &srv,QMainWindow* win) : gui(srv) , window(win){}
    QWidget* get_window();
    IncidentsWindow& start_timer();
    IncidentsWindow& stop_timer();
    GUI& get_gui();
    void update_types();
    void update();
};
