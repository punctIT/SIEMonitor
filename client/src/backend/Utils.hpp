#pragma once 
#include <string>
#include <chrono>
#include <ctime>
#include <format>

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