#pragma once

#include <string>
#include "../../log_parser/ThreadSafeQueue.h"
#include <unordered_map>
class SyslogListener{
    private:
        int port;
        int max_clients;
        int server_fd;
        ThreadSafeQueue <std::string> *queue;
        std::unordered_map<int, std::string> client_buffers;
        bool write_logs_in_queue(int fd);
    public:
        SyslogListener();
        SyslogListener& set_port(int port);
        SyslogListener& set_maximum_clients(int clients_numbers);
        SyslogListener& configure_server();
        SyslogListener& set_thread_safe_quere(ThreadSafeQueue <std::string>*);
        void listen_for_logs();
};

