#include "UpdateData.hpp"

#include <format>
#include <iostream>
#include <sstream>
#include <string>

std::string get_time(){
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

UpdateLogsData::UpdateLogsData(){
    this->logs_db.set_database_path("logsData.db");
    this->resolved_db.set_database_path("resolvedLogsData.db");
}
UpdateLogsData& UpdateLogsData::update_resolved(const std::string id,const std::string name){
    std::string sql = std::format("SELECT * FROM logs WHERE id='{}';",id);
    auto log=logs_db.get_data(sql.c_str());
    std::istringstream iss(log[0]);
    std::vector<std::string> data;
    std::string word="";
    int count = 0;
   
    while (count < 8 && iss >> word) {
        if(count == 7)
            break;
        data.push_back(word);
        count++;
    }

    std::streampos pos = iss.tellg();
    if (pos != -1) {
        std::string rest = log[0].substr(pos);
        data.push_back(rest);
    }
    
    std::string sql_insert= std::format("INSERT INTO logs (id,pri,timestamp,hostname,source,severity,resolvedTIME,resolvedRESPONDER,message) VALUES ({}, {}, '{}', '{}', '{}', '{}', '{}', '{}', '{}');",
        id,
        data[1],
        data[2]+" "+data[3],
        data[4],
        data[5],
        data[6],
        get_time(),
        name,
        data[7]
    );
    //std::cout<<sql_insert<<std::endl;
    resolved_db.run_command(sql_insert.c_str());
    sql=std::format("DELETE FROM logs where id = '{}';",id);
    logs_db.run_command(sql.c_str());
    return *this; 
}