#include "SplitLogs.hpp"

#include <sstream>
#include <vector>
#include <string>

SplitLog& SplitLog::set_log(std::string log ){
    this->log=log;
    return *this;
}
SplitLog& SplitLog::split(){
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
    } else {
        logs.push_back("");
    }
    splited_log=logs;
    return *this;
}
std::vector<std::string> SplitLog::get_splited_log(){
    return splited_log;
}