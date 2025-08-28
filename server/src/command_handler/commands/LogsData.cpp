#include "LogsData.hpp"
#include <format>

LogsData::LogsData(){
    this->logs_db.set_database_path("logsData.db");
}
LogsData& LogsData::set_fd(const int fd){
    this->fd=fd;
    return *this;
}
LogsData& LogsData:: get_logs_after_timestamp(const std::string timestamp){
    const std::string sql="SELECT * FROM logs;";
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }
    return *this;
}
LogsData& LogsData:: get_logs_number(const std::string timestamp){
    const std::string sql=std::format("SELECT COUNT(*) FROM logs WHERE timestamp >'{}';"
                                      ,timestamp);
    auto logs=logs_db.get_data(sql.c_str());
    std::string text=log_text_protocol(logs[0]);
    write(fd,text.c_str(),text.length());
    return *this;
}
LogsData& LogsData::get_logs_by_host(const std::string hostname,
                                   const std::string timestamp) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}';",
                                       timestamp,
                                       hostname);
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }                 
    return *this;
}
LogsData& LogsData::get_logs_by_host_and_source(const std::string hostname ,
                                              const std::string source,
                                              const std::string timestamp) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}';",
                                       timestamp,
                                       hostname,
                                       source
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}
LogsData& LogsData:: get_logs_by_host_and_severity(const std::string hostname , 
                                                const std::string severity, 
                                                const std::string timestamp){
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND severity='{}' AND hostname='{}';",
                                       timestamp,
                                       severity,
                                       hostname
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}
LogsData& LogsData:: get_logs_by_severity(const std::string severity,
                                       const std::string timestamp){
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND severity='{}';",
                                       timestamp,
                                       severity
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}
LogsData& LogsData::get_logs_by_host_source_severity(const std::string hostname,
                                                     const std::string source,
                                                     const std::string severity,
                                                     const std::string timestamp) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}' AND severity='{}';",
                                       timestamp,
                                       hostname,
                                       source,
                                       severity
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log);
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}
