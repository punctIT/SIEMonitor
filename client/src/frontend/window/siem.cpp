#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtCore/QTimer>  
#include <QtWidgets/QStackedWidget>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QEasingCurve>
#include <QtWidgets/QVBoxLayout>

#include "siem.h"
#include "home_screen/siem_home.h"
#include "incidents_screen/incidents_home.h"
#include "../style/style.h"

QWidget * SIEMWindow::get_side_menu(){

    QWidget *container= new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);

    QLabel* title_siem = new QLabel("SIEM");
    title_siem->setContentsMargins(20,100,20,100);
    QPushButton* home_btn= new QPushButton("Home");
    home_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton* incidents_btn= new QPushButton("Incidents");
    incidents_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton* analytic_btn = new QPushButton("Analytics");
    analytic_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton* threat_btn = new QPushButton("Threat Center");
    threat_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton* search_btn = new QPushButton("Search");
    search_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   
    QObject::connect(home_btn, &QPushButton::clicked, [this](){
        stack_window->setCurrentIndex(0); 
        homeWindow->start_update_timer();
        incidentsWindow->stop_timer();
        toggle_side_menu();
    });
    QObject::connect(incidents_btn, &QPushButton::clicked, [this](){
        stack_window->setCurrentIndex(1); 
        homeWindow->stop_update_timer();
        incidentsWindow->start_timer();
        toggle_side_menu();
    });
    QObject::connect(analytic_btn, &QPushButton::clicked, [this](){
        qDebug()<<"analitic";
        toggle_side_menu();
    });
    QObject::connect(threat_btn, &QPushButton::clicked, [this](){
        qDebug()<<"threat";
        toggle_side_menu();
    });
    QObject::connect(search_btn, &QPushButton::clicked, [this](){
        qDebug()<<"search";
        toggle_side_menu();
    });
    
    title_siem->setObjectName("title");

    layout->addWidget(title_siem, 0,0); 
    layout->addWidget(home_btn, 1,0);  
    layout->addWidget(incidents_btn, 2,0);
    layout->addWidget(analytic_btn, 3,0);
    layout->addWidget(threat_btn, 4,0);
    layout->addWidget(search_btn, 5,0);
    container->setStyleSheet(side_menu_style());
    return container;
}
void SIEMWindow::toggle_side_menu(){
    QLayoutItem *item = main_layout->itemAtPosition(1, 0);
    QWidget *widget = item->widget();
    if(toggle_menu){
            widget->show();    
            main_layout->setColumnStretch(0,1);
            main_layout->setColumnStretch(1,9);
        }
        else {
             widget->hide();    
             main_layout->setColumnStretch(0,0);
             main_layout->setColumnStretch(1,10);
        }
        toggle_menu=!toggle_menu;
}
QWidget * SIEMWindow::get_top_menu(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QPushButton* side_menu_btn= new QPushButton("Home");
    
    QObject::connect(side_menu_btn, &QPushButton::clicked, [this](){
        toggle_side_menu();
    });
    layout->addWidget(side_menu_btn,0,0);
    container->setStyleSheet(top_menu_style());
    return container;
}
QWidget * SIEMWindow::get_window(){
    QWidget *container= new QWidget(window);//for top meniu
    QWidget *second_container= new QWidget(window);//for meniu and main window
    QGridLayout *layout = new QGridLayout(container);
    
    main_layout = new QGridLayout(second_container);
    homeWindow = new SiemHomeWindow(gui,window);
    incidentsWindow= new IncidentsWindow(gui,window);
    toggle_menu=true;
    QWidget *side_menu = get_side_menu();
    QWidget *top_menu= get_top_menu();


    stack_window = new QStackedWidget();
    stack_window->addWidget(homeWindow->get_window());
    stack_window->addWidget(incidentsWindow->get_window());

    main_layout->setColumnStretch(0,0);
    main_layout->setColumnStretch(1,10);
    main_layout->addWidget(side_menu,1,0);
    main_layout->addWidget(stack_window,1,1);
    
    side_menu->hide();

    layout->addWidget(top_menu,0,0);
    layout->addWidget(second_container,1,0);
    return container;
}
void SIEMWindow::start_home_thread(){
    stack_window->setCurrentIndex(0); 
    homeWindow->start_update_timer();
}

SIEMWindow& SIEMWindow::set_username(QString user){
    username=user;
    homeWindow->set_username(user);
    incidentsWindow->set_username(user);
    return *this;
}