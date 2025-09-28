#include "map_widget.h"

#include <math.h>
#include <QtWidgets/QGridLayout>


#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>


QWidget* MapWidget::get_widget(){
    QWidget* container = new QWidget(window);
    QGridLayout* layout = new QGridLayout(container);
    

    label=new QLabel();
    label->setScaledContents(true);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    clear();
   
   
    layout->addWidget(label,0,0);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return container;
}
MapWidget& MapWidget::clear(){
    pixmap = QPixmap(w, h);
    pixmap.fill(Qt::transparent);
    QPixmap background("Imgs/map.png");
    QPainter painter(&pixmap);
    painter.drawPixmap(0, 0, background.scaled(pixmap.size(), Qt::KeepAspectRatioByExpanding));
    painter.end();
    label->setPixmap(pixmap);
    return *this;
}

QPointF latLonToPoint(double lat, double lon,
                      int width, int height)
{
   
    const double minLat = -75.0;   
    const double maxLat = 90.0;
    const double minLon = -164.0;
    const double maxLon = 180.0;

   
    double x = (lon - minLon) / (maxLon - minLon) * width;
    double y = (maxLat - lat) / (maxLat - minLat) * height;

    return QPointF(x, y);
}

MapWidget& MapWidget::add_location(double x,double y){
    QPainter painter(&pixmap);
    QColor color(255, 0, 0, 5);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(latLonToPoint(x,y,w,h), 70, 70);
    painter.end();
    label->setPixmap(pixmap); 
    return *this;
}