#include "InfoChart.hpp"
#include <format>
#include <string>
#include <iostream>




InfoChart::InfoChart( QMainWindow * win){
    window=win;
    total_logs=-1;
    error=-1;
    emergency=-1;
    alert=-1;
    critical=-1;
    warning=-1;
}

QWidget* InfoChart::get_chart(){
    series = new QPieSeries();
    series->append("Other", total_logs-error-emergency-alert-critical-warning);
    series->append("Error", error);
    series->append("Emergency", emergency);
    series->append("Alert", alert);
    series->append("Critical", critical);
    series->append("Warning", warning);

    QChart *chart = new QChart();
    chart->addSeries(series);
    series->setLabelsVisible(true);
    

    QChartView *chartView = new QChartView(chart, window);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}
QWidget* InfoChart::get_data_chart() {
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);

    QString total_string = QString::fromStdString(std::format("Total {}", total_logs));
    Total = new QLabel(total_string, container);

    QString emergency_string = QString::fromStdString(std::format("Emergency {}", emergency));
    Emergenty = new QLabel(emergency_string, container);

    QString alert_string = QString::fromStdString(std::format("Alert {}", alert));
    Alert = new QLabel(alert_string, container);

    QString critical_string = QString::fromStdString(std::format("Critical {}", critical));
    Critical = new QLabel(critical_string, container);

    QString error_string = QString::fromStdString(std::format("Error {}", error));
    Error = new QLabel(error_string, container);

    QString warning_string = QString::fromStdString(std::format("Warning {}", warning));
    Warning = new QLabel(warning_string, container);


    layout->addWidget(Total,0,0);
    layout->addWidget(Emergenty,1,0);
    layout->addWidget(Alert,1,1);
    layout->addWidget(Critical,2,0);
    layout->addWidget(Error,2,1);
    layout->addWidget(Warning,3,0);


    return container;
}
InfoChart& InfoChart::update(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    QString total_string = QString::fromStdString(std::format("Total {}", total_logs));
    Total->setText(total_string);

    QString emergency_string = QString::fromStdString(std::format("Emergency {}", emergency));
    Emergenty ->setText( emergency_string);

    QString alert_string = QString::fromStdString(std::format("Alert {}", alert));
    Alert ->setText(alert_string);

    QString critical_string = QString::fromStdString(std::format("Critical {}", critical));
    Critical ->setText(critical_string);

    QString error_string = QString::fromStdString(std::format("Error {}", error));
    Error->setText(error_string);

    QString warning_string = QString::fromStdString(std::format("Warning {}", warning));
    Warning->setText(warning_string);

    series->slices().at(0)->setValue(total_logs-error-emergency-alert-critical-warning);
    series->slices().at(1)->setValue(error);
    series->slices().at(2)->setValue(emergency);
    series->slices().at(3)->setValue(alert);
    series->slices().at(4)->setValue(critical);
    series->slices().at(5)->setValue(warning);

    return *this;
}
InfoChart& InfoChart::clear_data(){
    total_logs=-1;
    error=-1;
    emergency=-1;
    alert=-1;
    critical=-1;
    warning=-1;
    return *this;
}

InfoChart& InfoChart::update_info_data(const std::string severity){
    if(severity=="Alert"){
       alert+=1;
    }
    if(severity=="Emergency"){
        emergency+=1;
    }
    if(severity=="Error"){
      error+=1;
    }
    if(severity=="Warning"){
       warning+=1;
    }
    if(severity=="Critical"){
       critical+=1;
    }
    total_logs+=1;
    return *this;
}
InfoChart& InfoChart:: set_data(const std::vector<std::string> numbers){
     try {
           
        total_logs=std::stoi(numbers[0]);
        emergency=std::stoi(numbers[3]);
        alert=std::stoi(numbers[1]);
        critical=std::stoi(numbers[2]);
        error=std::stoi(numbers[4]);    
        warning=std::stoi(numbers[5]);

    }
    catch (const std::exception& e) {
        qDebug() << "Error converting:" ;
       
    }
    return *this;
}