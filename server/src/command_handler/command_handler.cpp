#include "command_handler.h"
#include <string>
#include <unistd.h> 
#include <vector>
#include "commands/test.h"

HandleCommand& HandleCommand::set_file_descriptor(int fd){
    this->fd=fd;
    return *this;
}
HandleCommand& HandleCommand::set_username(std::string name){
    this->username=name;
    return *this;
}
void HandleCommand::run(std::vector<std::string> args){
    if(args[0]=="test"){
       Test test;
       test.test(fd);
       return;
    }
   
    std::string msg="error , invalid command";
    int e=write(fd,msg.c_str(),msg.size());
    if( e < 0){
        throw std::runtime_error("Write to client , error");
    }
    
    
}