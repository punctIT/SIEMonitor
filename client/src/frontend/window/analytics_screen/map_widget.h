#pragma once 

#include <QtWidgets/QMainWindow>
#include <QtGui/QPixmap>
#include <QtWidgets/QLabel>

class MapWidget{
    private:
        QMainWindow *window;
        QPixmap pixmap;
        QLabel *label;
        int w=2560,h=1430;
    public:
        MapWidget(QMainWindow *win):window(win){};
        QWidget* get_widget();
        MapWidget& clear();
        MapWidget& add_location(double x,double y);
};