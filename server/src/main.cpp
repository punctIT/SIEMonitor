#include <iostream>
#include <thread> 
#include "network/syslog/SyslogListener.h"
#include <unistd.h>
#include "network/clients_conections/ClientListener.h"

void syslog_server(){
    SyslogListener a;
    try{
        a.set_port(514)
         .set_maximum_clients(100)
         .configure_server();
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;  
    }   

    try{
        a.listen_for_logs();
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;  
    }
}
int main() {
    std::thread syslog(syslog_server);
    syslog.detach();
    start_client();
   
}