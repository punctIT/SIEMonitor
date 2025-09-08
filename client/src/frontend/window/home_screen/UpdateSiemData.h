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


class SiemHomeWindow;

class UpdateSiemData : public QObject {
    Q_OBJECT
    
    public:
        UpdateSiemData(SiemHomeWindow* parent = nullptr) : siem(parent),running(false){}
        void Start() {
            running=true;
        }
        void Stop(){
            running=false;
        }
    public slots:
        void doWork(){
                while(true){
                    if(!running)
                        continue;
                    QThread::msleep(2000);
                    emit updateSIEM();
                }
            
        }
        
    signals:
        void updateSIEM();
        

    private:
        std::atomic <bool> running;
        SiemHomeWindow* siem;
        
};
