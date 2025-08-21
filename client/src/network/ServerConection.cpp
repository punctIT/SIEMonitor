#include "ServerConection.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



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

    if (connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("connect");
    }
    return *this;
}
void ServerConection::sent_receive(){
    write(server_fd, "Salut server!", 13);
    char buffer[1024];
    int bytes = read(server_fd, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Raspuns de la server: %s\n", buffer);
    }

}
void ServerConection::close_connection(){
    close(server_fd);
}
