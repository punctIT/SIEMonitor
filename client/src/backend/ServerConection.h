#pragma once 
#include <string>
#include "../utils/ThreadSafeQueue.h"
#include <optional>
class ServerConection{
    private:
        ThreadSafeQueue <std::string> responses;
        std::string ip;
        int port;
        int server_fd;
        void close_connection();
    public:
        ServerConection();
        ServerConection& set_server_adress(std::string);
        ServerConection& set_server_port(int);
        ServerConection& configure_connection();
        std::optional<std::string> get_response();
        void receive();
        void sent(std::string);
        void receive_start();
        
};