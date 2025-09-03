#pragma once 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <mutex>

class InfoChart{
    private:
        std::mutex infoChartMutex;
        int total_logs;
        int error;
        int emergency;
        int alert;
        int critical;
        int warning;

        QLabel *Total;
        QLabel *Error;
        QLabel *Emergenty;
        QLabel *Alert;
        QLabel *Critical;
        QLabel *Warning;
    public:
        InfoChart();
        QWidget* get_chart();
        InfoChart& update();

        InfoChart& set_total(int n);
        InfoChart& count_total();

        InfoChart& set_error(int n);
        InfoChart& count_error();

        InfoChart& set_emergenty(int n);
        InfoChart& count_emergenty();

        InfoChart& set_alert(int n);
        InfoChart& count_alert();

        InfoChart& set_critical(int n);
        InfoChart& count_critial();

        InfoChart& set_warning(int n);
        InfoChart& count_warning();

        
};