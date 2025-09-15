#pragma once 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>


#include <mutex>
#include <vector>
class InfoChart{
    private:
        QMainWindow *window;
        std::mutex infoChartMutex;

        QBarSet *set;
        QValueAxis *axisY;

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

        QBarSeries *series;
        
    public:
        InfoChart(QMainWindow *win);
        QWidget* get_data_chart();
        QWidget* get_chart();
        InfoChart& update();
        InfoChart& clear_data();

        InfoChart& update_info_data(const std::string category);
        InfoChart& set_data(const std::vector<std::string> numbers);
        
};