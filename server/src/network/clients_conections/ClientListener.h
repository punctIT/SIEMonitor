#pragma once 
#include <unistd.h>
#include <arpa/inet.h>

class ClientListener{
    private:
        int port;
        int server_fd;
        void send_receive(int);
    public:
    ClientListener();
    ClientListener& set_port(int);
    void server_configure();
    void start_listen();
};