#include <format>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtCore/QTimer>  
#include <QtWidgets/QStackedWidget>

#include "siem.h"
#include "home_screen/siem_home.h"
#include "incidents_screen/incidents_home.h"

QWidget * SIEMWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    homeWindow = new SiemHomeWindow(gui,window);
    incidentsWindow= new IncidentsWindow(gui,window);

    QLineEdit *cmd = new QLineEdit(container);
    QPushButton *stop= new QPushButton("stop",container);
    QObject::connect(stop, &QPushButton::clicked, [this](){stack_window->setCurrentIndex(1);});

    stack_window = new QStackedWidget();
    stack_window->addWidget(homeWindow->get_window());
    stack_window->addWidget(incidentsWindow->get_window());

    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,999);
    layout->addWidget(cmd,0,0);
    layout->addWidget(stop,0,1);
    layout->addWidget(stack_window,1,1);
    return container;
}
void SIEMWindow::start_home_thread(){
    stack_window->setCurrentIndex(0); 
    homeWindow->create_update_thread()
               .start_update_thread();
}
