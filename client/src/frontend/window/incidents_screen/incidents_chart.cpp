#include "Incidents_chart.hpp"
#include <QtWidgets/QWidget>


IncidentsChart::IncidentsChart(QMainWindow *win){
    window=win;
}
QWidget* IncidentsChart::get_info_data_table(){
    QFrame* card = new QFrame;
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(QString("background: %1; border-radius: 10px; padding: 10px;"));

    QGridLayout* cardLayout = new QGridLayout(card);
    total=new QLabel("Total 0");
    unresolved = new QLabel("Unresolved 0");
    resolved = new QLabel("Resolved 0");
    for(int i=0;i<3;++i){
        logs_data.push_back(new QLabel(""));
        cardLayout->addWidget(logs_data[i],2,i);
    }
    cardLayout->addWidget(total,0,0);
    cardLayout->addWidget(resolved,1,0);
    cardLayout->addWidget(unresolved,1,1);
    return card;
}
QWidget* IncidentsChart::get_charts(){
    QWidget *container = new QWidget(window);
    QGridLayout *layout = new QGridLayout(container);


    series_resolved = new QPieSeries(container);
    series_resolved->append("Resolved",12);
    series_resolved->append("Unresolved",12);
    series_resolved->setHoleSize(0.35); 
    series_resolved->setLabelsVisible(true);
    QChart *chart_resolved = new QChart();
    chart_resolved->addSeries(series_resolved);
    
    chart_resolved->legend()->hide();

    QChartView *chartViewResolved = new QChartView(chart_resolved, window);
    chartViewResolved->setRenderHint(QPainter::Antialiasing);


    series_logs= new QPieSeries(container);
    series_logs->append("HIGH",12);
    series_logs->append("MEDIUM",12);
    series_logs->append("LOW",12);
    series_logs->setHoleSize(0.35); 

    QChart *chart = new QChart();
    chart->addSeries(series_logs);
    series_logs->setLabelsVisible(true);
    chart->legend()->hide();


    QChartView *chartView = new QChartView(chart, window);
    chartView->setRenderHint(QPainter::Antialiasing);

    
    

    layout->addWidget(get_info_data_table(),0,0);
    layout->addWidget(chartView,0,2);
    layout->addWidget(chartViewResolved,0,1);
    return container;

}


IncidentsChart& IncidentsChart::update_data_resolved(const std::vector<std::string> data_requested){
    series_resolved->clear();
    series_resolved->append("Unresolved", std::stoi(data_requested[0]));
    series_resolved->append("Resolved", std::stoi(data_requested[1]));
    series_resolved->setLabelsVisible(true);
    resolved->setText(QString::fromStdString(std::format("Resolved {}",data_requested[1])));
    unresolved->setText(QString::fromStdString(std::format("Unresolved {}",data_requested[0])));
    return *this;
}
IncidentsChart& IncidentsChart::update_data_logs(const std::vector<std::string> data_requested){
    series_logs->clear();
    for(int i=0;i<3;i++){
        logs_data[i]->setText("");
    }
    int i=0;
    int sum=0;
    for(auto data :data_requested){
        std::string number="";
        std::string name="";
        //qDebug()<<QString::fromStdString(data);
        for(auto ch : data){
            if(isdigit(ch))
                number+=ch;
            else name+=ch;
        }
        //qDebug() << "number:" << QString::fromStdString(number) << "name:" << QString::fromStdString(name);
        if(number!="0")
            series_logs->append(QString::fromStdString(name), std::stoi(number));
        sum+=std::stoi(number);
        logs_data[i]->setText(QString::fromStdString(std::format("{} {}",name,number)));
        ++i;
    }
    total->setText(QString::fromStdString(std::format("Total {}",sum)));
    series_logs->setLabelsVisible(true);
    return *this;
}
