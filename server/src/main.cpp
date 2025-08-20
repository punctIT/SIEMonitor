#include "network/ServerSyslog.h"
#include "network/ServerClient.h"
int main() {
    SyslogServer syslog_server;
    syslog_server.run_in_background();
    syslog_server.start_worker_threads();
    ClientReceiverServer clients_server;
    clients_server.start_server();
   
}