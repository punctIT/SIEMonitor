#include <iostream>
#include <thread> 
#include "syslog_connections/SyslogListener.h"
#include <unistd.h>
#include "clients_conections/ClientListener.h"
#include "../utils/ThreadSafeQueue.h"
#include "../log_parser/LogDatabaseWriter.h"

class SyslogServer{
    private:
        ThreadSafeQueue <std::string> queue;
        SyslogListener a;
        LogDatabaseWriter writer;
        
    public:
        SyslogServer(){
            std::cout<<"Start Syslog server"<<std::endl;
            writer.set_thread_safe_quere(&this->queue);
        }
        void start_server(){
            try{
                a.set_port(514)
                .set_maximum_clients(100)
                .set_thread_safe_quere(&queue)
                .configure_server();
            }
            catch(const std::exception& e){
                std::cout << e.what() << std::endl;  
                return;
            }   

            try{
                a.listen_for_logs();
            }
            catch(const std::exception& e){
                std::cout << e.what() << std::endl;
                return;  
            }
        }
        void run_in_background(){
            std::thread syslog(&SyslogServer::start_server, this);
            syslog.detach();
        }
        void start_worker_threads(){
            std::thread w1(&LogDatabaseWriter::write_logs, &this->writer, 1);
            std::thread w2(&LogDatabaseWriter::write_logs, &this->writer, 2);
            std::thread w3(&LogDatabaseWriter::write_logs, &this->writer, 3);
            std::thread w4(&LogDatabaseWriter::write_logs, &this->writer, 4);
            w1.detach();
            w2.detach();
            w3.detach();
            w4.detach();
        }
};