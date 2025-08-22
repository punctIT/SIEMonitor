#pragma once 
#include <unistd.h>
#include <arpa/inet.h>
#include "Authentification/AuthService.h"

class ClientListener{
    private:
        int port;
        int server_fd;
        void send_receive(int);
        AuthService auth;
    public:
    ClientListener();
    ClientListener& set_port(int);
    void server_configure();
    void start_listen();
};