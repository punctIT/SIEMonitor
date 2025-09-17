#include "InfoChart.hpp"
#include <format>
#include <string>
#include <iostream>


#include <QtCharts/QBarCategoryAxis>
#include <QtGui/QColor>

InfoChart::InfoChart( QMainWindow * win){
    window=win;
    total_logs=0;
    error=0;
    emergency=0;
    alert=0;
    critical=0;
    warning=0;
}

QWidget* InfoChart::get_chart(){
    QWidget *container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    series = new QBarSeries();
    set = new QBarSet("Incidents");
    *set << (1) << 2 << 3 << 4 << 5 <<6;
    QColor orange(255, 165, 0);
    set->setBrush(orange);
    series->append(set);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd); 
    series->setLabelsFormat("@value");     
    


    Warning->setObjectName("data_msg");
    Critical->setObjectName("data_msg");
    Total->setObjectName("data_msg");
    Alert->setObjectName("data_msg");
    Emergenty->setObjectName("data_msg");
    Error->setObjectName("data_msg");

    QStringList categories;
    categories << "Other" << "Error" << "Emergency" << "Alert" << "Critical" << "Warning";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    
    axisY = new QValueAxis();
    axisY->setRange(0, 100);  
    axisY->setTickCount(11); 
    axisX->setLinePen(Qt::NoPen);
    axisY->setLinePen(Qt::NoPen);
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->setBackgroundBrush(Qt::NoBrush);   
    chart->setBackgroundPen(Qt::NoPen);     
    

    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart, window);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setAttribute(Qt::WA_TranslucentBackground);
    layout->addWidget(chartView,0,0);
    container->setObjectName("data");
    return container;
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
    
    container->setObjectName("data");
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

    set->replace(0, total_logs-error-emergency-alert-critical-warning);
    set->replace(1, error);
    set->replace(2, emergency);
    set->replace(3, alert);
    set->replace(4, critical);
    set->replace(5, warning);
    axisY->setRange(0, total_logs);  
    axisY->setTickCount(total_logs/10); 
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