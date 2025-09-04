#include "LogsData.hpp"
#include <format>
#include <string>
#include <chrono>
#include <ctime>

std::string get_current_time(){
   auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::string year = std::to_string(tm.tm_year + 1900); 
    std::string month = std::to_string(tm.tm_mon + 1);    
    std::string day = std::to_string(tm.tm_mday);       

    if (month.length() == 1){
        month = "0" + month;
    }
        
    if (day.length() == 1){
        day = "0" + day;
    } 
    char buffer[9]; 
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm);
    std::string time_result(buffer);

    std::string result = std::format("{}-{}-{} {}",year,month,day,time_result);
    return result;
}

std::string get_final_date(const std::string& timestamp_end){
    std::string end_date=timestamp_end;
    if(timestamp_end.empty()){
        end_date=get_current_time();
    }
    return end_date;
}

LogsData::LogsData(){
    this->logs_db.set_database_path("logsData.db");
}
LogsData& LogsData::set_fd(const int fd){
    this->fd=fd;
    return *this;
}
LogsData& LogsData:: get_logs_after_timestamp(const std::string timestamp,const std::string timestamp_end){   
    const std::string sql=std::format("SELECT * FROM logs WHERE timestamp > '{}' AND timestamp <= '{}';",
                                      timestamp,
                                      get_final_date(timestamp_end)
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GLAT");
        write(fd,text.c_str(),text.length());
    }
    //std::cout<<timestamp<<" "<<get_final_date(timestamp_end)<<std::endl;
    return *this;
}
LogsData& LogsData:: get_logs_number(const std::string timestamp,const std::string timestamp_end){
    const std::string sql=std::format("SELECT COUNT(*) FROM logs WHERE timestamp >'{}' AND timestamp <= '{}';",
                                      timestamp,
                                      get_final_date(timestamp_end)
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    std::string text=log_text_protocol(logs[0],"GLN");
    write(fd,text.c_str(),text.length());
    return *this;
}

LogsData& LogsData::get_logs_by_host(const std::string hostname,
                                     const std::string timestamp,
                                     const std::string timestamp_end) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}' AND timestamp <= '{}';",
                                       timestamp,
                                       hostname,
                                       get_final_date(timestamp_end)
                                    );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GLH");
        write(fd,text.c_str(),text.length());
    }                 
    return *this;
}
LogsData& LogsData::get_logs_by_host_and_source(const std::string hostname ,
                                               const std::string source,
                                               const std::string timestamp,
                                               const std::string timestamp_end) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}' AND timestamp <= '{}';",
                                       timestamp,
                                       hostname,
                                       source,
                                       get_final_date(timestamp_end)
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
                                                const std::string timestamp,
                                                const std::string timestamp_end){
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND severity='{}' AND hostname='{}' AND timestamp <= '{}';",
                                       timestamp,
                                       severity,
                                       hostname,
                                       get_final_date(timestamp_end)
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GLHSe");
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}
LogsData& LogsData:: get_logs_by_severity(const std::string severity,
                                       const std::string timestamp,
                                       const std::string timestamp_end){
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND severity='{}' AND timestamp <= '{}';",
                                       timestamp,
                                       severity,
                                       get_final_date(timestamp_end)
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
                                                     const std::string timestamp,
                                                     const std::string timestamp_end) {
    const std::string sql =std::format("SELECT * FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}' AND severity='{}' AND timestamp <= '{}';",
                                       timestamp,
                                       hostname,
                                       source,
                                       severity,
                                       get_final_date(timestamp_end)
                                      );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GLSoSe");
        write(fd,text.c_str(),text.length());
    }  
    return *this;
}


LogsData& LogsData:: get_logs_number_severity(const std::string severity,
                                              const std::string timestamp,
                                              const std::string timestamp_end){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND severity='{}' AND timestamp <='{}';",
                                        timestamp,
                                        severity,
                                        get_final_date(timestamp_end)
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
                                                   const std::string timestamp,
                                                   const std::string timestamp_end){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE severity='{}' AND hostname='{}' AND timestamp > '{}' AND timestamp <='{}';",
                                        severity,
                                        host,
                                        timestamp,
                                        get_final_date(timestamp_end)
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
                                                          const std::string timestamp,
                                                          const std::string timestamp_end){
    const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE severity='{}' AND hostname='{}' and source='{}' AND timestamp > '{}' AND timestamp <='{}';",
                                        severity,
                                        host,
                                        source,
                                        timestamp,
                                        get_final_date(timestamp_end)
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
                                         const std::string timestamp,
                                         const std::string timestamp_end){

   const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND hostname='{}' AND timestamp <='{}';",
                                        timestamp,
                                        host,
                                        get_final_date(timestamp_end)
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
                                                const std::string timestamp,
                                                const std::string timestamp_end){

   const std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp > '{}' AND hostname='{}' AND source='{}' AND timestamp <= '{}';",
                                        timestamp,
                                        host,
                                        source,
                                        get_final_date(timestamp_end)
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