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
QWidget* InfoChart::get_chart() {
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
    return *this;
}

InfoChart& InfoChart::set_total(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    total_logs=n;
    return *this;
}
InfoChart& InfoChart::count_total(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    total_logs+=1;
    return *this;
}

InfoChart& InfoChart::set_error(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    error=n;
    return *this;
}
InfoChart& InfoChart::count_error(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    error+=1;
    return *this;
}

InfoChart& InfoChart::set_emergenty(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    emergency=n;
    return *this;
}
InfoChart& InfoChart::count_emergenty(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    emergency+=1;
    return *this;
}

InfoChart& InfoChart::set_alert(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    alert=n;
    return *this;
}
InfoChart& InfoChart::count_alert(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    alert+=1;
    return *this;

}
InfoChart& InfoChart::set_warning(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    warning=n;
    return *this;
}
InfoChart& InfoChart::count_warning(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    warning+=1;
    return *this;
}

InfoChart& InfoChart::set_critical(int n){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    critical=n;
    return *this;
}
InfoChart& InfoChart::count_critial(){
    std::lock_guard<std::mutex> lock(infoChartMutex);
    critical+=1;
    return *this;
}
InfoChart& InfoChart::update_info_data(const std::string severity){
    if(severity=="Alert"){
       this->count_alert();
    }
    if(severity=="Emergency"){
        this->count_emergenty();
    }
    if(severity=="Error"){
       this->count_error();
    }
    if(severity=="Warning"){
        this->count_warning();
    }
    if(severity=="Critical"){
       this->count_critial();
    }
    this->count_total();
    return *this;
}
InfoChart& InfoChart:: set_data(const std::string number){
     try {
        int num = std::stoi(number);    
        if(this->total_logs==-1){
            total_logs=num;
            return *this;
        }
        if(this->emergency==-1){
            emergency=num;
            return *this;
        }
        if(this->alert==-1){
            alert=num;
            return *this;
        }
        if(this->critical==-1){
            critical=num;
            return *this;
        }
        if(this->error==-1){
            error=num;
            return *this;
        }
        if(this->warning==-1){
            warning=num;
            return *this;
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Error converting:" << QString::fromStdString(number);
       
    }
    return *this;
}