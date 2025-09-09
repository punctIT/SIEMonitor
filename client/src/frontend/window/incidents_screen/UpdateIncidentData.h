#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>


#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>


class IncidentsWindow;

class UpdateIncindetData : public QObject {
    Q_OBJECT
    
    public:
        UpdateIncindetData(IncidentsWindow* parent = nullptr) : siem(parent),running(false){}
        void Start() {
            running=true;
        }
        void Stop(){
            running=false;
        }
    public slots:
        void doWork(){
                while(running){
                    QThread::msleep(2000);
                    emit updateIncident();
                }
            
        }
        
    signals:
        void updateIncident();
        

    private:
        std::atomic <bool> running;
        IncidentsWindow* siem;
        
};
