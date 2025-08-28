#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "../../utils/ProtocolHandler.h"
#include "../../utils/DBComandExecutor.h"

#define DEFAULT_DATE "2000-01-01 00:00:00"

class LogsData:ProtocolHandler{
    int fd;
    DBComandExecutor logs_db;
    public:
        LogsData();
        LogsData& set_fd(const int fd);
        LogsData& get_logs_after_timestamp(const std::string timestamp=DEFAULT_DATE);
        LogsData& get_logs_number();
        LogsData& get_logs_by_host(const std::string hostname,
                                   const std::string timestamp=DEFAULT_DATE);
        LogsData& get_logs_by_host_and_source(const std::string host ,
                                              const std::string source,
                                              const std::string timetamp=DEFAULT_DATE);
        LogsData& get_logs_by_severity(const std::string severity,
                                       const std::string timestamp=DEFAULT_DATE);

        LogsData& get_logs_by_host_and_severity(const std::string host , 
                                                const std::string severity, 
                                                const std::string timestamp=DEFAULT_DATE);
        LogsData& get_logs_by_host_source_severity(const std::string host,
                                                   const std::string souce,
                                                   const std::string severity,
                                                   const std::string timestamp=DEFAULT_DATE);

};