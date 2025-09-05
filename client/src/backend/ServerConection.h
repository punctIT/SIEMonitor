#pragma once 
#include <string>
#include <optional>
#include <QtCore/QObject>
#include <QtCore/QString>


class ServerConection : public QObject {
    Q_OBJECT
    private:
        std::string ip;
        int port;
        int server_fd;
        void close_connection();
    public:
        ServerConection();
        ServerConection& set_server_adress(std::string);
        ServerConection& set_server_port(int);
        ServerConection& configure_connection();
        void receive();
        void sent(std::string);
        void receive_start();
    signals:
        void loginResponse(QString resp);  
        void logData(QString log);
        void logDataNumbers(QString log);
        void usersData(QString data);      
        void alertsData(QString data);      
        void genericResponse(QString data); 
        
};