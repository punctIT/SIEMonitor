#include "ServerConection.h"
#include "UpdateWorker.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>


ServerConection::ServerConection(){
    std::cout<<"Init server connection"<<std::endl;
}
ServerConection& ServerConection::set_server_adress(std::string ip){
    this->ip=ip;
    return *this;
}
ServerConection& ServerConection::set_server_port(int port){
    this->port=port;
    return *this;
}
ServerConection& ServerConection::configure_connection(){
    struct sockaddr_in server_addr;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("Socket Error");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);

    if (inet_pton(AF_INET,this->ip.c_str(), &server_addr.sin_addr) <= 0) {
       throw std::runtime_error("init pton");
    }

    if (::connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("connect");
    }
    return *this;
}
void ServerConection::receive(const QString& msg){
    if (msg.startsWith("[login]")){
        emit loginResponse(msg.mid(QString("[login]").length()));
        return;
    }
    if (msg.startsWith("[LOG]")){
        QString msg2=msg.mid(QString("[LOG]").length());
        if(msg2.startsWith("[LN]")){
            QString msg3=msg2.mid(QString("[LN]").length());
            emit logTable(msg3);
        }
        else {
            emit logData(msg2);
        }
        return;
    }
    if (msg.startsWith("[DATA]")){
        QString msg2=msg.mid(QString("[DATA]").length());
         if(msg2.startsWith("[GLND]")){
            QString msg3=msg2.mid(QString("[GLND]").length());
            emit logDataNumbers(msg3);
        }
        return;
    }
    if (msg.startsWith("[INC]")){
        QString msg2=msg.mid(QString("[INC]").length());
        if(msg2.startsWith("[TAB]")){
            emit IncidentsResponseTable(msg2.mid(QString("[INC]").length()));
        }
        return;
    }
    emit genericResponse(msg);
              
}
ServerConection& ServerConection::sent(std::string cmd){  
    cmd+="\n\r";  
    write(server_fd, cmd.c_str(), cmd.size());
    return *this;
}
void ServerConection::receive_start(){
    QThread* updateThread = new QThread(this);
    UpdateWorker *worker = new UpdateWorker(this, server_fd);
    connect(worker, &UpdateWorker::updateRequested, this, &ServerConection::receive);
    connect(updateThread, &QThread::started, worker, &UpdateWorker::doWork);
    connect(updateThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(updateThread, &QThread::finished, updateThread, &QObject::deleteLater);

    worker->moveToThread(updateThread);
    updateThread->start();
}
void ServerConection::close_connection(){
    close(server_fd);
}
