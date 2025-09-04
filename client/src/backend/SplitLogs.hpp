#pragma once 
#include <sstream>
#include <vector>
#include <string>

class SplitLog{
    private:
        std::string log;
        std::vector<std::string> splited_log; 
    public:
        SplitLog& set_log(std::string log);
        SplitLog& split_log();
        SplitLog& split_all();
        std::vector<std::string> get_splited_log();
        std::string get_severity();
        std::string get_message();
        std::string get_host();
        std::string get_source();
        int get_id();
        int get_pri();
};