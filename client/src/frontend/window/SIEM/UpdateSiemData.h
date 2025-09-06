#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>


class SIEMWindow;

class UpdateSiemData : public QObject {
    Q_OBJECT

    public:
        UpdateSiemData(SIEMWindow* parent = nullptr) : siem(parent){}
    public slots:
        void doWork(){
                while(true){
                    QThread::msleep(2000);
                    emit updateSIEM();
                }
            
        }
        
    signals:
        void updateSIEM();
        

    private:
        SIEMWindow* siem;
        
};
