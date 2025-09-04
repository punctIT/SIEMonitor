#include "SplitLogs.hpp"

#include <sstream>
#include <vector>
#include <string>

SplitLog& SplitLog::set_log(std::string log ){
    this->log=log;
    return *this;
}
SplitLog& SplitLog::split_log(){
    std::istringstream iss(log);
    std::vector<std::string> logs;
    std::string word="";
    int count = 0;
   
    while (count < 7 && iss >> word) {
        logs.push_back(word);
        count++;
    }

    std::streampos pos = iss.tellg();
    if (pos != -1) {
        std::string rest = log.substr(pos);
        logs.push_back(rest);
    }
    splited_log=logs;
    return *this;
}
SplitLog& SplitLog::split_all(){
    std::istringstream iss(log);
    std::vector<std::string> logs;
    std::string word="";
    while (iss >> word) {
        logs.push_back(word);
    }
    splited_log=logs;
    return *this;
}
std::string SplitLog::get_severity(){
    if(splited_log.size()>=6){
        return splited_log[6];
    }
    return "";
}
std::string SplitLog::get_message(){
    if(splited_log.size()>=7){
        return splited_log[7];
    }
    return "";
}
std::string SplitLog::get_time(){
    if(splited_log.size()>=6){
        return splited_log[3];
    }
    return "";
}
std::string SplitLog::get_host(){
    if(splited_log.size()>=6){
        return splited_log[4];
    }
    return "";
}
std::string SplitLog::get_source(){
    if(splited_log.size()>=6){
        return splited_log[5];
    }
    return "";
}
std::vector<std::string> SplitLog::get_splited_log(){
    return splited_log;
}