#pragma once 
#include <string>
#include <optional>
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>

class QObject;
class QThread;
class QString;

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
        ServerConection&  sent(std::string);
        void receive_start();
    signals:
        void loginResponse(QString resp);  
        void logData(QString log);
        void logDataNumbers(QString log);
        void logTable(QString log);     
        void resolvedTable(QString log);     
        void resolvedTableUpdate(QString log);
        void genericResponse(QString data);
        void onlineUsers(QString users); 


        void IncidentsResponseTable(QString data); 
        void IncidentsChartData(QString data);
        void IncidentsResolved(QString data);
        void HostsEnum(QString data);
    private slots:
        void receive(const QString& now);
        
};