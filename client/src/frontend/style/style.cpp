#include "style.h"


QString main_style(){
    QString style = "QMainWindow { background-color: #222222ff; }\
                     QLabel{ text-color: #ffffffff}";
    return style;
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
            background-color: #1c1c1c;
            border: 1px solid #16a085;
            border-radius: 5px;
            padding: 5px;
            color: #ecf0f1;
        }

        QPushButton {
            background-color: #16a085;
            border: none;
            border-radius: 5px;
            padding: 8px;
            color: white;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #16a085;
        }

        QPushButton:pressed {
            background-color: #149174;
        }
    )";
    return Style;
}