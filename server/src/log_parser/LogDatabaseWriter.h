#pragma once 

#include "ThreadSafeQueue.h"
#include <string>


class LogDatabaseWriter{
    ThreadSafeQueue <std::string> *queue;
    public:
        LogDatabaseWriter();
        LogDatabaseWriter& set_thread_safe_quere(ThreadSafeQueue <std::string>*);
        void write_logs(int number);
};