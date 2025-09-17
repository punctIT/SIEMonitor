#include "style.h"


QString main_style(){
    QString style = R"(
        QMainWindow { background-color:rgb(26, 26, 26); }
        QLabel{ color: #ffffffff}
    )";
    return style;
}

QString siem_home_style(){
    return R"(
        QLabel#welcome_msg {
            font-weight: bold;
            font-size: 36px;
            color: white;
        }
        QBarCategoryAxis{
            color: white;
        }
        QChartView{
            background-color:rgb(53, 53, 53);
            color: #ffffffff;
        }
        QHeaderView::section {
            background-color:rgb(53, 53, 53);
            color: #ffffffff;
        }
          QScrollBar:vertical {
            border: none;
            background: #333;
            width: 12px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: #666;
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