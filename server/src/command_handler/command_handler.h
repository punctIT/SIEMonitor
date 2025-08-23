#pragma once

#include <iostream>
#include <string>
#include <vector>

class HandleCommand{
    private:
        int fd;
        std::string username;
    public:
        HandleCommand& set_file_descriptor(int fd);
        HandleCommand& set_username(std::string);
        void run(std::vector<std::string>);
};