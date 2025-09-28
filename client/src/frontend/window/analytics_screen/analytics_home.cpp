#include "analytics_home.h"
#include "../../../backend/Utils.hpp"
#include "../../../backend/SplitLogs.hpp"
#include "../../gui.h"
#include "map_widget.h"
#include "location_table.hpp"
#include "../../style/style.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* AnalyticsWindow::get_filter_menu(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("text");

    layout->addWidget(text,0,0);
    container->setObjectName("map");
    return container;
}

void AnalyticsWindow::bind_signals(){
    connect(updateTimer, &QTimer::timeout, this, &AnalyticsWindow ::update);

    QObject::connect(&gui.get_server(),&ServerConection::LocationData,[this](QString resp){
        SplitLog logs_data;
        logs_data.set_log(resp.toStdString()).split_all();
        auto logs=logs_data.get_splited_log();
        if(logs[0]=="RESTART"){
            mapWidget->clear();
            locationTable->clear();
        }
        else {
            //qDebug()<<resp;
            try{
                mapWidget->add_location(std::stod(logs[3]),std::stod(logs[2]));
                locationTable->update_data(logs);
            }
            catch(std::exception &e){};
            
        }
        
       
    });
}

QWidget* AnalyticsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    mapWidget = new MapWidget(window);
    locationTable = new LocationTable(window);

    QLabel *text = new QLabel("Incidents");
    updateTimer=new QTimer(window);
    
    layout->setColumnStretch(0,65);
    layout->setColumnStretch(1,35);

    QGridLayout *up_layout = new QGridLayout();
    QGridLayout *left_layout = new QGridLayout();
    left_layout->addWidget(mapWidget->get_widget(),0,0);
    left_layout->addWidget(get_filter_menu(),1,0);
    up_layout->addWidget(locationTable->get_widget(),0,1);
    up_layout->addLayout(left_layout,0,0);
    layout->addLayout(up_layout,0,0);
    

    bind_signals();
    container->setStyleSheet(analytics_style());
    container->setObjectName("map");
    return container;
}

void AnalyticsWindow::update(){
    //gui.get_server().sent("GLSHS ALL NONE NONE");
    gui.get_server().sent("GLNL 1000");
}

AnalyticsWindow & AnalyticsWindow ::start_timer(){
    gui.get_server().sent("GLNL 1000");
    updateTimer->start(2000);
    return *this;
}
AnalyticsWindow & AnalyticsWindow ::stop_timer(){
    updateTimer->stop();
    return *this;
}