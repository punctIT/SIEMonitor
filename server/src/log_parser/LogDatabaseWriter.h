#pragma once 

#include "../utils/ThreadSafeQueue.h"
#include "../utils/DBComandExecutor.h"
#include <string>
#include <sqlite3.h>

class GetIpData;

class LogDatabaseWriter{
    ThreadSafeQueue <std::string> *queue;
    DBComandExecutor db;
    DBComandExecutor db_location;
    GetIpData *ip_data;

    public:
        LogDatabaseWriter();
        ~LogDatabaseWriter();
        LogDatabaseWriter& set_thread_safe_quere(ThreadSafeQueue <std::string>*);
        void write_logs(int number);
};