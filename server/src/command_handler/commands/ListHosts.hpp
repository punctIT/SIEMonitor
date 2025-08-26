#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "../../utils/ProtocolHandler.h"
#include "../../utils/DBComandExecutor.h"

class ListHosts:ProtocolHandler{
    int fd;
    DBComandExecutor logs_db;
    public:
        ListHosts();
        ListHosts& set_fd(const int &fd);
        ListHosts& get_hosts();
        ListHosts& get_sources(const std::string &host);
};