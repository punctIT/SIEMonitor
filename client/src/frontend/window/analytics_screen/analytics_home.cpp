#include "analytics_home.h"
#include "../../../backend/Utils.hpp"
#include "../../../backend/SplitLogs.hpp"
#include "../../gui.h"
#include "map_widget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* AnalyticsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    mapWidget = new MapWidget(window);
    QLabel *text = new QLabel("Incidents");
    updateTimer=new QTimer(window);
    connect(updateTimer, &QTimer::timeout, this, &AnalyticsWindow ::update);
    
    layout->addWidget(mapWidget->get_widget());


    QObject::connect(&gui.get_server(),&ServerConection::LocationData,[this](QString resp){
        SplitLog logs_data;
        logs_data.set_log(resp.toStdString()).split_all();
        auto logs=logs_data.get_splited_log();
        if(logs[0]=="RESTART"){
            mapWidget->clear();
        }
        else {
            //qDebug()<<QString::fromStdString(logs[2]+" "+logs[3])
            try{
                mapWidget->add_location(std::stod(logs[3]),std::stod(logs[2]));
            }
            catch(std::exception &e){};
            
        }
       
    });

    return container;
}

void AnalyticsWindow::update(){
    //gui.get_server().sent("GLSHS ALL NONE NONE");
    gui.get_server().sent("GLNL 100");
}

AnalyticsWindow & AnalyticsWindow ::start_timer(){
    gui.get_server().sent("GLNL 100");
    updateTimer->start(2000);
    return *this;
}
AnalyticsWindow & AnalyticsWindow ::stop_timer(){
    updateTimer->stop();
    return *this;
}