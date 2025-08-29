#include "siem.hpp"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include "../../gui.hpp"
#include "../../../backend/SplitLogs.hpp"

QWidget * SIEMWindow::get_window(){
    QWidget *container= new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    QLineEdit *cmd = new QLineEdit(container);
    QPushButton *run = new QPushButton("run",container);

    QObject::connect(run, &QPushButton::clicked, [this,cmd](){
        std::string c= cmd->text().toStdString();

        gui.get_server().sent(c);
    });
    
    QObject::connect(&gui.get_server(),&ServerConection::genericResponse,[this](QString resp){
        SplitLog split;
        split.set_log(resp.toStdString())
             .split();
        for(auto l : split.get_splited_log()){
            qDebug() <<QString::fromStdString(l)<<"\n"; 
        }
        qDebug()<<"\n\n"; 
    });

    layout->addWidget(cmd, 1, 0);        
    layout->addWidget(run, 1, 1);   
    return container;
}