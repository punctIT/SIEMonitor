#pragma once 
#include <unistd.h>
#include <arpa/inet.h>
#include "Authentication/AuthService.h"
#include "../../utils/ProtocolHandler.h"

class ClientListener:public ProtocolHandler{
    private:
        int port;
        int server_fd;
        void send_receive(int);
        AuthService auth;
    public:
    ClientListener();
    ClientListener& set_port(int);
    ClientListener& server_configure();
    ClientListener& start_listen();
};