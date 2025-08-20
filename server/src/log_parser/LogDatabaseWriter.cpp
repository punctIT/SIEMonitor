#include "LogDatabaseWriter.h"
#include <iostream>

LogDatabaseWriter::LogDatabaseWriter(){
    std::cout<<"Start writing log in DataBase"<<std::endl;
}
LogDatabaseWriter& LogDatabaseWriter::set_thread_safe_quere(ThreadSafeQueue <std::string>* queue){
    this->queue=queue;
    return *this;
}
void LogDatabaseWriter::write_logs(int number){
    while(true){
        auto log_data=this->queue->pop();
        if (log_data.has_value()){
            std::cout<<"THREAD["<<number<<"] "<<log_data.value()<<std::endl;
        }
    }
}