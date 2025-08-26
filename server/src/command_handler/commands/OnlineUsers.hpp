#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "../../utils/ProtocolHandler.h"
#include "../../utils/DBComandExecutor.h"

class OnlineUsers:ProtocolHandler{
    int fd;
    DBComandExecutor users_db;
    public:
        OnlineUsers();
        OnlineUsers& set_fd(const int &fd);
        OnlineUsers& run();
};