#include "SyslogListener.h"
#include <iostream>

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

SyslogListener::SyslogListener(){
    std::cout<<"OK";
}
SyslogListener& SyslogListener::set_port(int port){
    this->port=port;
    return *this;
}
SyslogListener& SyslogListener::set_maximum_clients(int clients_number){
    this->max_clients=clients_number;
    return *this;
}
SyslogListener& SyslogListener::configure_server(){
    struct sockaddr_in addr;
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd < 0) {
        throw std::runtime_error("Error socket");
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("Error bind");
    }

    if (listen(server_fd, 5) < 0) {
        throw std::runtime_error("Error listen");
    }
    return *this;
}
void SyslogListener::listen_for_logs(){
    std::cout << "[INFO] Server listen at " << this->port << std::endl;
    
    const int buffer_size=100;
    char buffer[buffer_size];
    std::vector<pollfd> fds;
    pollfd server_poll;
    server_poll.fd = this->server_fd;
    server_poll.events = POLLIN;
    fds.push_back(server_poll);

    while (true) {
        const int ret = poll(fds.data(), fds.size(), -1);
        if (ret < 0) {
            throw std::runtime_error("Error poll");
        }
        for (size_t i = 0; i < fds.size(); i++) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == server_fd) {
                    int client_fd = accept(server_fd, nullptr, nullptr);
                    if (client_fd < 0) {
                        perror("accept");
                    } else {
                        pollfd client_poll;
                        client_poll.fd = client_fd;
                        client_poll.events = POLLIN;
                        fds.push_back(client_poll);
                        std::cout << "[INFO] Client connected: fd=" << client_fd << std::endl;
                    }
                } else {
                    int n = read(fds[i].fd, buffer, buffer_size - 1);
                    if (n <= 0) {
                        std::cout << "[INFO] Client disconnected: fd=" << fds[i].fd << std::endl;
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
           
                    } else {
                        buffer[n] = '\0';
                        std::cout << "[LOG] " << buffer;
                    }
                }
            }
        }
    }

    close(server_fd);
}
