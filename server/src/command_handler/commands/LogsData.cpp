#include "LogsData.hpp"
#include <format>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <iostream>

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

LogsData::LogsData(){
    this->logs_db.set_database_path("logsData.db");
}
LogsData& LogsData::set_fd(const int fd){
    this->fd=fd;
    return *this;
}
LogsData& LogsData:: get_logs(const std::string time_start,const std::string time_end , const std::string nr){   
    std::string sql=std::format("SELECT * FROM logs WHERE timestamp >= '{}' AND timestamp < '{}' ORDER BY id DESC LIMIT {};",
                            time_start,
                            time_end,
                            nr
                        );
    //std::cout << "SQL: " << sql << std::endl;
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"GL");
        write(fd,text.c_str(),text.length());
    }
    //std::cout<<time_start<<" "<<time_end<<std::endl;
    return *this;
}

LogsData& LogsData::get_last_n(std::string nr){
    auto time = get_current_time();
    std::string sql = std::format("SELECT * FROM logs WHERE timestamp < '{}' ORDER BY id DESC LIMIT {};",time,nr);
    auto logs=logs_db.get_data(sql.c_str());

    std::string text=log_text_protocol("RESTART","LN");
    write(fd,text.c_str(),text.length());
    for(auto log :logs){
        std::string text=log_text_protocol(log,"LN");
        write(fd,text.c_str(),text.length());
    }
    return *this;
}

LogsData& LogsData::get_logs_number_data(const std::string time){
    std::vector<std::string> numbers;
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
                                                     const std::string source,
                                                     const std::string time_start,
                                                     const std::string time_end,
                                                     const std::string search
                                            ){

    std::string sql;
    bool limit=true;
    if(severity=="HIGH"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Emergency','Alert','Critical')");
        limit=false;
    }
    if(severity=="MEDIUM"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Error','Warning')");
    }
    if(severity=="LOW"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Notice','Informational','Debug')");
    }
     if(severity=="ALL"){
        sql=std::format("SELECT * FROM LOGS WHERE severity in ('Notice','Informational','Debug','Error','Warning','Emergency','Alert','Critical')");
    }
    if(host!="NONE"){
        sql=std::format(" {} AND hostname='{}'",sql,host);
    }
    if(source!="NONE"){
        sql=std::format(" {} AND source='{}'",sql,source);
    }
    if(time_start=="NONE NONE"){
        std::string text=severity_text_protocol("[RESTART]","TAB");
        write(fd,text.c_str(),text.length());
        sql=std::format(" {} AND timestamp < '{}' ",sql,get_current_time());
    }
    else {
        sql=std::format(" {} AND timestamp < '{}' AND timestamp >= '{}'",sql,time_end,time_start);
        //std::cout<<timestamp<<" "<<time<<std::endl;
    }
    if(search!="NONE"){
        sql=std::format(" {} AND (hostname LIKE '%{}%' OR source LIKE '%{}%' OR message LIKE '%{}%')",sql,search,search,search);
    }
    if(limit){
        sql+=" ORDER BY id DESC LIMIT 150;";
    }
    else {
        sql+=";";
    }
    auto logs=logs_db.get_data(sql.c_str());
    for(auto log :logs){
        std::string text=severity_text_protocol(log,"TAB");
        write(fd,text.c_str(),text.length());
    }
     if(time_start=="NONE NONE"){
        std::string text=severity_text_protocol("[TOP]","TAB");
        write(fd,text.c_str(),text.length());
     }
    return *this;
}

 LogsData& LogsData::get_logs_number_by_type(const std::string type){
    std::vector<std::string> data;
    if(type=="HIGH"){
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Critical');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Critical",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Emergency');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Emergency",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Alert');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Alert",logs[0]));
    }   
    else if(type=="MEDIUM"){
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Error');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Error",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Warning');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Warning",logs[0]));
       
    }
    else if(type=="LOW"){
        std::string sql=std::format("SELECT COUNT(*) FROM logs WHERE severity in ('Debug');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Debug",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM logs WHERE severity in ('Informational');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Informational",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM logs WHERE severity in ('Notice');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Notice",logs[0]));
    }
    else {
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Emergency','Alert','Critical');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}High",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Error','Warning');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Medium",logs[0]));
        sql=std::format("SELECT COUNT(*) FROM logs WHERE severity in ('Notice','Informational','Debug');");
        logs=logs_db.get_data(sql.c_str());
        data.push_back(std::format("{}Low",logs[0]));
    }
    if(!data.empty()){
        std::string text=get_text(data,"[GLNT]");
        write(fd,text.c_str(),text.length());
    }
    return *this;
 }
 LogsData& LogsData::get_resolve_number(const std::string type){
    std::vector<std::string> data;
    DBComandExecutor resolved_logs_db;
    resolved_logs_db.set_database_path("resolvedLogsData.db");
    if(type=="HIGH"){
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Emergency','Alert','Critical');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
        logs=resolved_logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
    }   
    else if(type=="MEDIUM"){
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS WHERE severity in ('Error','Warning');");
         auto logs=logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
         logs=resolved_logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
       
    }
    else if(type=="LOW"){
       std::string sql=std::format("SELECT COUNT(*) FROM logs WHERE severity in ('Notice','Informational','Debug');");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
        logs=resolved_logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
    }
    else {
        std::string sql=std::format("SELECT COUNT(*) FROM LOGS;");
        auto logs=logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
        logs=resolved_logs_db.get_data(sql.c_str());
        data.push_back(logs[0]);
    }
    
    if(!data.empty()){
        std::string text=get_text(data,"[GRN]");
        write(fd,text.c_str(),text.length());
    }
    return *this;
 }