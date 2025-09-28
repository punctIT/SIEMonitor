#include "style.h"


QString main_style(){
    QString style = R"(
        QMainWindow { background-color:rgb(26, 26, 26); }
        QLabel{ color: #ffffffff}
    )";
    return style;
}
QString analytics_style(){

 return R"(
        QWidget#map {
            background-color:rgba(135, 135, 135, 0.09);
            border-radius: 10px;
            border: 1px solid rgb(160, 100, 22);
            font-weight: bold;
        }
    
      
        QBarCategoryAxis{
            color: white;
        }

        QHeaderView::section {
            background-color:rgb(20, 20, 20);
            color: #ffffffff;
        }
        QScrollBar:vertical {
            border: none;
            background: rgb(53, 53, 53);
            width: 12px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: rgb(53, 53, 53);
            min-height: 20px;
            border-radius: 5px;
        }

        QScrollBar::handle:vertical:hover {
            background: #888;
        }
        QListWidget{
            Background-color:rgb(17, 17, 17);
            border: 1px solid rgb(160, 100, 22);
            
        }
        QListWidget::item { 
            padding: 5px 5px 5px;
            font-weight: bold;
            color: #ffffffff;
            font-size: 15px;
        }
        QListWidget::item:selected{
            background-color:rgb(66, 66, 66);
            color: rgb(255, 217, 0);
        }
    )";
}
QString siem_home_style(){
    return R"(
        QWidget#bg {
            background-color:rgba(45, 45, 45, 0.09);
            border-radius: 10px;
            border: 1px solid rgb(160, 100, 22);
            font-weight: bold;
        }
        QWidget#data {
            background-color:rgba(0, 0, 0, 0.09);
            border-radius: 10px;
            font-weight: bold;
        }
    
        QLabel#welcome_msg {
            font-weight: bold;
            font-size: 36px;
            color: white;
            margin: 10px 10px 10px 10px;
        }
        QLabel#data_msg{
            font-weight: bold;
            font-size: 20x;
            color: white;
            margin: 10px 10px 10px 10px;
        }
        QBarCategoryAxis{
            color: white;
        }
        QChartView{
            background-color:rgb(53, 53, 53);
            color: #ffffffff;
        }
        QHeaderView::section {
            background-color:rgb(20, 20, 20);
            color: #ffffffff;
        }
        QScrollBar:vertical {
            border: none;
            background: rgb(53, 53, 53);
            width: 12px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: rgb(53, 53, 53);
            min-height: 20px;
            border-radius: 5px;
        }

        QScrollBar::handle:vertical:hover {
            background: #888;
        }
        QTreeWidget::item { 
            padding: 5px 5px 5px;
            font-weight: bold;
            color: #ffffffff;
            font-size: 15px;
        }
        QTreeWidget::item:selected{
            background-color:rgb(112, 112, 112);
            color: rgb(255, 217, 0);
        }
        QTreeWidget{ 
            background-color:rgb(17, 17, 17);
             border: 1px solid rgb(160, 100, 22);
        }
        QListWidget{
            Background-color:rgb(17, 17, 17);
            border: 1px solid rgb(160, 100, 22);
            
        }
        QListWidget::item { 
            padding: 5px 5px 5px;
            font-weight: bold;
            color: #ffffffff;
            font-size: 15px;
        }
        QListWidget::item:selected{
            background-color:rgb(66, 66, 66);
            color: rgb(255, 217, 0);
        }
    )";
}

QString login_style(){
    QString Style = R"(
        QWidget {
            background-color: #1c1c1c;
        }

        QLabel {
            color: #ecf0f1;
            font-size: 18px;
            font-weight: bold;
        }

        QLineEdit {
            background-color:rgb(0, 0, 0);
            border: 1px solid rgb(160, 100, 22);
            border-radius: 5px;
            padding: 5px;
            color: #ecf0f1;
        }

        QPushButton {
            background-color:rgb(160, 128, 22);
            border: none;
            border-radius: 5px;
            padding: 8px;
            color: white;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color:rgb(160, 84, 22);
        }

        QPushButton:pressed {
            background-color:rgb(145, 95, 20);
        }
    )";
    return Style;
}
QString side_menu_style(){
    QString Style = R"(
        QLabel#title {
            color: #ecf0f1;
            font-size: 48px;
            font-weight: bold;
        }
        QPushButton {
            background-color:rgb(29, 29, 29);
            border: 1px solid  rgb(160, 100, 22);
            border-radius: 5px;
            padding: 8px;
            color: white;
            font-size: 20px;
           
        }

        QPushButton:hover {
            background-color:rgb(160, 84, 22);
        }

        QPushButton:pressed {
            background-color:rgb(145, 95, 20);
        }
    )";
    return Style;
}
QString top_menu_style(){
    QString Style = R"(
        QPushButton {
            background-color:rgb(29, 29, 29);
            border: none;
            text-align: left; 
            padding-left: 10px;
            border-radius: 5px;
            padding: 8px;
            color: white;
            font-size: 18px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color:rgb(160, 84, 22);
        }

        QPushButton:pressed {
            background-color:rgb(145, 95, 20);
        }
    )";
    return Style;
}
QString incidnets_style(){
    return R"(
        QWidget#bg {
            background-color:rgba(49, 49, 49, 0.09);
            border-radius: 10px;
            border: 1px solid rgb(160, 100, 22);
            font-weight: bold;
        }
        QLabel#data_msg{
            font-weight: bold;
            font-size: 20x;
            color: white;
            margin: 10px 10px 10px 10px;
        }
        QPushButton {
            background-color:rgb(29, 29, 29);
            border: none;
            border-radius: 5px;
            padding: 8px;
            color: white;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color:rgb(160, 84, 22);
        }

        QPushButton:pressed {
            background-color:rgb(145, 95, 20);
        }
        QLineEdit {
            background-color: #1a1a1a;
            border: 1px solid rgb(160, 100, 22);
            border-radius: 5px;
            padding: 5px;
            color: #ecf0f1;
        }

        QLabel { color: #ffffffff}
        QWidget#frame {
            background-color:rgba(49, 49, 49, 0.15);
            color: #ffffffff;
        }
        QChartView{
            background-color:rgb(26, 26, 26);
            color: #ffffffff;
        }
        QHeaderView::section {
            background-color:rgb(20, 20, 20);
            color: #ffffffff;
        }
        QScrollBar:vertical {
            border: none;
            background: rgb(53, 53, 53);
            width: 12px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: rgb(53, 53, 53);
            min-height: 20px;
            border-radius: 5px;
        }

        QScrollBar::handle:vertical:hover {
            background: #888;
        }
        QListWidget{
            Background-color:rgb(17, 17, 17);
            border: 1px solid rgb(160, 100, 22);
            
        }
        QListWidget::item { 
            padding: 5px 5px 5px;
            font-weight: bold;
            color: #ffffffff;
            font-size: 15px;
        }
        QListWidget::item:selected{
            background-color:rgb(66, 66, 66);
            color: rgb(255, 217, 0);
        }
        QComboBox {
        background-color: #222;
        color: #fff;
        border: 1px solid #444;
        border-radius: 4px;
        padding: 4px 8px;
    }

    QComboBox:hover, QComboBox:focus {
        border: 1.5px solid #ffa500; 
    }

    QComboBox::drop-down {
        background-color: #222;
        border-left: 1px solid #444;
    }

    QComboBox::down-arrow {
        width: 12px;
        height: 12px;
    }

    QComboBox QAbstractItemView {
        background-color: #1a1a1a;
        color: #fff;
        border: 1px solid #333;
        selection-background-color: #ffa500; 
        selection-color: #222;
    }
    )";
}
