#include "LogsData.hpp"
#include <format>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>


std::string get_current_time(){
    auto now = std::chrono::system_clock::now()- std::chrono::seconds(30); 
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
LogsData& LogsData:: get_logs(const std::string time_start,const std::string time_end , const std::string nr){   
    std::string sql=std::format("SELECT * FROM logs WHERE timestamp > '{}' AND timestamp <= '{}' ORDER BY id DESC LIMIT {};",
                            time_start,
                            time_end,
                            nr
                        );
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GL");
        write(fd,text.c_str(),text.length());
    }
    //std::cout<<timestamp<<" "<<get_final_date(timestamp_end)<<std::endl;
    return *this;
}

LogsData& LogsData::get_last_n(std::string nr){
    auto time = get_current_time();
    std::string sql = std::format("SELECT * FROM logs WHERE timestamp <'{}' ORDER BY id DESC LIMIT {};",time,nr);
    auto logs=logs_db.get_data(sql.c_str());

    std::string text=log_text_protocol("RESTART","LN");
    write(fd,text.c_str(),text.length());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"LN");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}

LogsData& LogsData::get_logs_number_data(){
    std::vector<std::string> numbers;
    auto time = get_current_time();
    std::string sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp < '{}';",time);
    auto n=logs_db.get_data(sql.c_str());
    numbers.push_back(n[0]);
    for(auto type:{"Alert","Critical","Emergency","Error","Warning"}){
        sql = std::format("SELECT COUNT(*) FROM logs WHERE timestamp < '{}' AND severity='{}';",time,type);
        auto n=logs_db.get_data(sql.c_str());
        numbers.push_back(n[0]);
    }
    std::string text=get_text(numbers,"[DATA]","[GLND]");
    write(fd,text.c_str(),text.length());
    return *this;
}

LogsData& LogsData::get_logs_by_severity_host_source(const std::string severity,
                                                     const std::string host,
                                                     const std::string source
                                            ){

    std::string sql;
    bool limit=true;
    auto time = get_current_time();
    if(severity=="HIGH"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Emergency','Alert','Critical')",severity);
        limit=false;
    }
    if(severity=="MEDIUM"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Error','Warning')",severity);
    }
    if(severity=="LOW"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Notice','Informational','Debug')",severity);
    }
     if(severity=="ALL"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Notice','Informational','Debug','Error','Warning','Emergency','Alert','Critical')",severity);
    }
    if(host!="NONE"){
        sql=std::format("{} AND hostname='{}'",sql,host);
    }
    if(source!="NONE"){
        sql=std::format("{} AND source='{}'",sql,source);
    }
    sql=std::format("{} AND timestamp <'{}'",sql,time);
    if(limit){
        sql+="AND resolved=0 LIMIT 150;";
    }
    else {
        sql+="AND resolved=0;";
    }
    
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=severity_text_protocol(log,"");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}