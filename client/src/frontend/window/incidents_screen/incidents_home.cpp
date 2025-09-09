#include "incidents_home.h"
#include "../../../backend/Utils.hpp"
#include "../../gui.h"

#include "UpdateIncidentData.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QWidget* IncidentsWindow::get_window(){
    QWidget *container= new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);
    QLabel *text = new QLabel("Incidents");
    layout->addWidget(text);


    QObject::connect(&gui.get_server(),&ServerConection::IncidentsResponse,[this](QString resp){
        qDebug()<<resp;
    });

    return container;
}

void IncidentsWindow::update(){
    gui.get_server().sent("GLSHS ALL NONE NONE");
}

IncidentsWindow& IncidentsWindow::create_update_thread(){
    if(worker!=nullptr && updateThread!=nullptr)
        return *this;
    gui.get_server().sent("caca");
    std::string datetime = get_current_time();
    updateThread = new QThread(this);
    worker = new UpdateIncindetData(this);
    connect(worker, &UpdateIncindetData::updateIncident, this, &IncidentsWindow::update);
    connect(updateThread, &QThread::started, worker, &UpdateIncindetData::doWork);
    connect(updateThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(updateThread, &QThread::finished, updateThread, &QObject::deleteLater);

    worker->Start();
    worker->moveToThread(updateThread);
    updateThread->start();
    
    return *this;
}
IncidentsWindow& IncidentsWindow::stop_update_thread(){
    if (worker) {
        worker->Stop();             
    }
    if (updateThread) {
        updateThread->quit();       
        updateThread->wait();    
    }

    worker = nullptr;
    updateThread = nullptr;

    return *this;
}