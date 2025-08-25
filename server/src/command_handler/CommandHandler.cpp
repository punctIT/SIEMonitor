#include "CommandHandler.h"
#include <string>
#include <unistd.h> 
#include <vector>
#include "commands/test.h"
#include "commands/OnlineUsers.hpp"

HandleCommand& HandleCommand::set_file_descriptor(int fd){
    this->fd=fd;
    return *this;
}
HandleCommand& HandleCommand::set_username(std::string name){
    this->username=name;
    return *this;
}
void HandleCommand::run(std::vector<std::string> args){
    int e =0;
    if(args[0]=="test"){
       Test test;
       test.test(fd);
       return;
    }
    if(args[0]=="users"){
        try{
            OnlineUsers users;
            users.set_fd(fd)
                 .run();
        }
        catch(std::exception &err){
            std::cout<<"[USER COMMAND]"<<err.what()<<std::endl;
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="hosts"){
        
        return;
    }
    std::string msg="error , invalid command";
    e=write(fd,msg.c_str(),msg.size());
    if( e < 0){
        throw std::runtime_error("Write to client , error");
    }
    
    
}