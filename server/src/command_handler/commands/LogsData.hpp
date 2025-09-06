#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "../../utils/ProtocolHandler.h"
#include "../../utils/DBComandExecutor.h"

#define DEFAULT_DATE "2000-01-01 00:00:00"
#define DEFALUT_DATE_END ""
class LogsData: ProtocolHandler{
    int fd;
    DBComandExecutor logs_db;
    public:
        LogsData();
        LogsData& set_fd(const int fd);
        LogsData& get_logs(const std::string time_start,
                           const std::string time_end ,
                           const std::string nr
        );
        LogsData& get_last_n(const std::string n);

        LogsData& get_logs_number(const std::string timestamp=DEFAULT_DATE,
                                  const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_number_host(const std::string host,
                                       const std::string timestamp=DEFAULT_DATE,
                                       const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_number_severity(const std::string severity,
                                           const std::string timestamp=DEFAULT_DATE,
                                           const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_number_severity_host(const std::string severity,
                                                const std::string host,
                                                const std::string timestamp=DEFAULT_DATE,
                                                const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_number_severity_host_source(const std::string severity,
                                                       const std::string host,
                                                       const std::string source,
                                                       const std::string timestamp=DEFAULT_DATE,
                                                       const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_number_host_source(const std::string host,
                                              const std::string source,
                                              const std::string timestamp=DEFAULT_DATE,
                                              const std::string timestamp_end=DEFALUT_DATE_END);
};