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
        std::string text=log_text_protocol(log,"GLAT");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}
LogsData& LogsData:: get_logs_number(const std::string timestamp){
    const std::string sql=std::format("SELECT COUNT(*) FROM logs WHERE timestamp >'{}';"
                                      ,timestamp);
    auto logs=logs_db.get_data(sql.c_str());
    std::string text=log_text_protocol(logs[0],"GLN");
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
        std::string text=log_text_protocol(log,"GLH");
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
        std::string text=log_text_protocol(log,"GLHSo");
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
        std::string text=log_text_protocol(log,"GLHSe");
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
        std::string text=log_text_protocol(log,"GLSe");
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
        std::string text=log_text_protocol(log,"GLSoSe");
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}


LogsData& LogsData:: get_logs_number_severity(const std::string severity,
                                              const std::string timestamp){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND severity='{}';",
                                        timestamp,
                                        severity
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    if(logs.size()){
        std::string text=log_text_protocol(logs[0],"GLNSe");
        write(fd,text.c_str(),text.length());
    }
    else {
        std::string text=log_text_protocol("0","GLNSe");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}
LogsData& LogsData:: get_logs_number_severity_host(const std::string severity,
                                                   const std::string host,
                                                   const std::string timestamp){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE severity='{}' AND hostname='{}' AND timestamp > '{}' ;",
                                        severity,
                                        host,
                                        timestamp
                                       );
    auto logs=logs_db.get_data(sql.c_str());
    if(logs.size()){
        std::string text=log_text_protocol(logs[0],"GLNSeH");
        write(fd,text.c_str(),text.length());
    }
    else {
        std::string text=log_text_protocol("0","GLNSeH");
        write(fd,text.c_str(),text.length());
    }
    
    return *this;
}
LogsData& LogsData:: get_logs_number_severity_host_source(const std::string severity,
                                                          const std::string host,
                                                          const std::string source,
                                                          const std::string timestamp){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE severity='{}' AND hostname='{}' and source='{}' AND timestamp > '{}';",
                                        severity,
                                        host,
                                        source,
                                        timestamp
                                       );
    auto logs=logs_db.get_data(sql.c_str());
    if(logs.size()){
        std::string text=log_text_protocol(logs[0],"GLNSeHSo");
        write(fd,text.c_str(),text.length());
    }
    else {
        std::string text=log_text_protocol("0","GLNSeHSo");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}
LogsData& LogsData::get_logs_number_host(const std::string host,
                                         const std::string timestamp){

   const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND hostname='{}';",
                                        timestamp,
                                        host
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    if(logs.size()){
        std::string text=log_text_protocol(logs[0],"GLNH");
        write(fd,text.c_str(),text.length());
    }
    else {
        std::string text=log_text_protocol("0","GLNH");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}
LogsData& LogsData::get_logs_number_host_source(const std::string host,
                                                const std::string source,
                                                const std::string timestamp){

   const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}';",
                                        timestamp,
                                        host,
                                        source
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    if(logs.size()){
        std::string text=log_text_protocol(logs[0],"GLNHSo");
        write(fd,text.c_str(),text.length());
    }
    else {
        std::string text=log_text_protocol("0","GLNHSo");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}