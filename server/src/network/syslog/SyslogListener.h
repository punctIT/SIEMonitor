#pragma once

#include <string>

class SyslogListener{
    private:
        int port;
        int max_clients;
        int server_fd;
        int buffer_size;
    public:
        SyslogListener();
        SyslogListener& set_port(int port);
        SyslogListener& set_maximum_clients(int clients_numbers);
        SyslogListener& configure_server();
        void listen_for_logs();
};

