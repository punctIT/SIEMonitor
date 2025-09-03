#include "InfoChart.hpp"
#include <format>

InfoChart::InfoChart(){
    total_logs=0;
    error=0;
    emergency=0;
    alert=0;
    critical=0;
    warning=0;
}
QWidget* InfoChart::get_chart() {
    QWidget *container = new QWidget();
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
    total_logs=n;
    return *this;
}
InfoChart& InfoChart::count_total(){
    total_logs+=1;
    return *this;
}

InfoChart& InfoChart::set_error(int n){
    error=n;
    return *this;
}
InfoChart& InfoChart::count_error(){
    error+=1;
    return *this;
}

InfoChart& InfoChart::set_emergenty(int n){
    emergency=n;
    return *this;
}
InfoChart& InfoChart::count_emergenty(){
    emergency+=1;
    return *this;
}

InfoChart& InfoChart::set_alert(int n){
    alert=n;
    return *this;
}
InfoChart& InfoChart::count_alert(){
    alert+=1;
    return *this;

}
InfoChart& InfoChart::set_warning(int n){
    warning=n;
    return *this;
}
InfoChart& InfoChart::count_warning(){
    warning+=1;
    return *this;
}

InfoChart& InfoChart::set_critical(int n){
    critical=n;
    return *this;
}
InfoChart& InfoChart::count_critial(){
    critical+=1;
    return *this;
}