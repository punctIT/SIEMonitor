#pragma once 
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>

#include <mutex>
#include <vector>
#include <utility> 
#include <string>
class IncidentsChart{
    private:
        QMainWindow *window;
        std::mutex infoChartMutex;
        
        std::vector<std::pair<std::string,int>> data;
        QPieSeries *series_logs;
        QPieSeries *series_resolved;

        QLabel *total;
        QLabel *resolved;
        QLabel *unresolved;
        std::vector<QLabel*> logs_data;
        
        QWidget* get_info_data_table();
    public:
        IncidentsChart(QMainWindow *win);
        QWidget* get_charts();
        IncidentsChart& update();
      

        IncidentsChart& update_data_resolved(const std::vector<std::string> data_requested);
        IncidentsChart& update_data_logs(const std::vector<std::string> data_requested);
        
};