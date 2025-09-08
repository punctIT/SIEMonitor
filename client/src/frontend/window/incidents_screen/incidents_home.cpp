#include "incidents_home.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Incidents");
    layout->addWidget(text);
    return container;
}