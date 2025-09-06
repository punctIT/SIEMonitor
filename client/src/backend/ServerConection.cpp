#include "ServerConection.h"
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
void ServerConection::receive(){
    char buffer[1024];
    std::string recvBuffer;

    while (true) {
        int bytes = read(server_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) {
            std::cerr << "Connection closed or error\n";
            exit(0);
        }

        buffer[bytes] = '\0';
        recvBuffer.append(buffer, bytes);
        size_t pos;
        while ((pos = recvBuffer.find("\n\r\n\r")) != std::string::npos) {
            std::string message = recvBuffer.substr(0, pos);
            //std::cout<<message<<std::endl;
            QString msg = QString::fromUtf8(message);
            
            if (msg.startsWith("[login]")){
                emit loginResponse(msg.mid(QString("[login]").length()));
            }
            if (msg.startsWith("[LOG]")){
                QString msg2=msg.mid(QString("[LOG]").length());
                if(msg2.startsWith("[GLN")){
                    emit logDataNumbers(msg2);
                }
                else if(msg2.startsWith("[LN0000000]")){
                    QString msg3=msg2.mid(QString("[LN0000000]").length());
                    emit logTable(msg3);
                }
                else {
                    emit logData(msg2);
                }
               
            }
            else {
                emit genericResponse(msg);
            }
            
            recvBuffer.erase(0, pos + 4);
        }
    }
    
}
ServerConection& ServerConection::sent(std::string cmd){  
    cmd+="\n\r";  
    write(server_fd, cmd.c_str(), cmd.size());
    return *this;
}
void ServerConection::receive_start(){
    std::thread t1(&ServerConection::receive, this);
    t1.detach();
}
void ServerConection::close_connection(){
    close(server_fd);
}
