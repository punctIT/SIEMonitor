#include "CommandHandler.h"
#include <string>
#include <unistd.h> 
#include <vector>

#include "commands/test.h"
#include "commands/OnlineUsers.hpp"
#include "commands/ListHosts.hpp"
#include "commands/LogsData.hpp"
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
        try{
            ListHosts host;
            host.set_fd(fd)
                .get_hosts();
        }
         catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="source"){
        try{
            ListHosts host;
            host.set_fd(fd)
                .get_sources(args[1]);
        }
         catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GL"){
        try{
            LogsData logs;
            if(args.size()==6){
                const std::string time_start=args[1]+' '+args[2];
                const std::string time_end=args[3]+' '+args[4];
                logs.set_fd(fd)
                    .get_logs(time_start,time_end,args[5]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="LN"){
        try{
            LogsData logs;
            logs.set_fd(fd)
                .get_last_n(args[1]);
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLND"){
        try{
            LogsData logs;
            logs.set_fd(fd)
                .get_logs_number_data();   
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLSHS"){
        try{
            LogsData logs;
            logs.set_fd(fd)
                .get_logs_by_severity_host_source(args[1],args[2],args[3]);   
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    
    std::string msg="error , invalid command";
    e=write(fd,msg.c_str(),msg.size());
    if( e < 0){
        throw std::runtime_error("Write to client , error");
    }
    
    
}