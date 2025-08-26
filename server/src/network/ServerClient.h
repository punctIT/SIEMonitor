#pragma once 
#include "clients_conections/ClientListener.h"
class ClientReceiverServer{
    ClientListener clients;
    public:
        void start_server(){
            clients.set_port(12345)
                   .server_configure()
                   .start_listen();
        }
};