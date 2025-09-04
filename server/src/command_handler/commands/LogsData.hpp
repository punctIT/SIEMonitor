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
        LogsData& get_logs_after_timestamp(const std::string timestamp=DEFAULT_DATE,
                                           const std::string timestamp_end=DEFALUT_DATE_END);
        LogsData& get_logs_number(const std::string timestamp=DEFAULT_DATE,
                                  const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_by_host(const std::string hostname,
                                   const std::string timestamp=DEFAULT_DATE,
                                   const std::string timestamp_end=DEFALUT_DATE_END);
        LogsData& get_logs_by_host_and_source(const std::string host ,
                                              const std::string source,
                                              const std::string timestamp=DEFAULT_DATE,
                                              const std::string timestamp_end=DEFALUT_DATE_END);
        LogsData& get_logs_by_severity(const std::string severity,
                                       const std::string timestamp=DEFAULT_DATE,
                                       const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_by_host_and_severity(const std::string host , 
                                                const std::string severity, 
                                                const std::string timestamp=DEFAULT_DATE,
                                                const std::string timestamp_end=DEFALUT_DATE_END);

        LogsData& get_logs_by_host_source_severity(const std::string host,
                                                   const std::string souce,
                                                   const std::string severity,
                                                   const std::string timestamp=DEFAULT_DATE,
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