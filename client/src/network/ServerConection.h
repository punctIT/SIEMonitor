#pragma once 
#include <string>

class ServerConection{
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
        void sent_receive();
        
};