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
    if(args[0]=="GLAT"){
        try{
            LogsData logs;
            if(args.size()==3){
                const std::string timestamp=args[1]+' '+args[2];
                logs.set_fd(fd)
                    .get_logs_after_timestamp(timestamp);
            }
            else {
                logs.set_fd(fd)
                    .get_logs_after_timestamp();
            }
           
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLN"){
        try{
            LogsData logs;
            if(args.size()==3){
                const std::string timestamp=args[1]+' '+args[2];
                logs.set_fd(fd)
                    .get_logs_number(timestamp);
            }
            else {
                logs.set_fd(fd)
                .get_logs_number();
            }
            
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLH"){
        try{
            LogsData logs;
            if(args.size()==4){
                const std::string timestamp=args[2]+' '+args[3];
                logs.set_fd(fd)
                    .get_logs_by_host(args[1],timestamp);
            }
            else {
                logs.set_fd(fd)
                   .get_logs_by_host(args[1]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLHSo"){
        try{
            LogsData logs;
            if(args.size()==5){
                const std::string timestamp=args[3]+" "+args[4];
                logs.set_fd(fd)
                    .get_logs_by_host_and_source(args[1],args[2],timestamp);
            }
            else {
                logs.set_fd(fd)
                    .get_logs_by_host_and_source(args[1],args[2]);
            }
            
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLSe"){
        try{
            LogsData logs;
            if(args.size()==4){
                const std::string timestamp=args[2]+" "+args[3];
                logs.set_fd(fd)
                    .get_logs_by_severity(args[1],timestamp);
            }
            else {
                logs.set_fd(fd)
                    .get_logs_by_severity(args[1]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLHSe"){
        try{
            LogsData logs;
            if(args.size()==5){
                const std::string timestamp=args[3]+" "+args[4];
                logs.set_fd(fd)
                    .get_logs_by_host_and_severity(args[1],args[2],timestamp);
            }
            else {
                logs.set_fd(fd)
                    .get_logs_by_host_and_severity(args[1],args[2]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLHSoSe"){
        try{
            LogsData logs;
            if(args.size()==6){
                const std::string timestamp=args[4]+" "+args[5];
                logs.set_fd(fd)
                    .get_logs_by_host_source_severity(args[1],args[2],args[3],timestamp);
            }
            else {
                logs.set_fd(fd)
                    .get_logs_by_host_source_severity(args[1],args[2],args[3]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLNSe"){
        try{
            LogsData logs;
            if(args.size()==4){
                const std::string timestamp=args[2]+" "+args[3];
                logs.set_fd(fd)
                    .get_logs_number_severity(args[1],timestamp);
                }
            else {
                logs.set_fd(fd)
                   .get_logs_number_severity(args[1]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
     if(args[0]=="GLNSeH"){
        try{
            LogsData logs;
            if(args.size()==5){
                const std::string timestamp=args[3]+" "+args[4];
                logs.set_fd(fd)
                    .get_logs_number_severity_host(args[1],args[2],timestamp);
                }
            else {
                logs.set_fd(fd)
                   .get_logs_number_severity_host(args[1],args[2]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLNSeHSo"){
        try{
            LogsData logs;
            if(args.size()==6){
                const std::string timestamp=args[4]+" "+args[5];
                logs.set_fd(fd)
                    .get_logs_number_severity_host_source(args[1],args[2],args[3],timestamp);
                }
            else {
                logs.set_fd(fd)
                   .get_logs_number_severity_host_source(args[1],args[2],args[3]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLNH"){
        try{
            LogsData logs;
            if(args.size()==4){
                const std::string timestamp=args[2]+" "+args[3];
                logs.set_fd(fd)
                    .get_logs_number_host(args[1],timestamp);
                }
            else {
                logs.set_fd(fd)
                   .get_logs_number_host(args[1]);
            }
        }
        catch(std::exception &err){
            write(fd,unexpected_error.c_str(),unexpected_error.size());
        }
        return;
    }
    if(args[0]=="GLNHSo"){
        try{
            LogsData logs;
            if(args.size()==5){
                const std::string timestamp=args[3]+" "+args[4];
                logs.set_fd(fd)
                    .get_logs_number_host_source(args[1],args[2],timestamp);
                }
            else {
                logs.set_fd(fd)
                    .get_logs_number_host_source(args[1],args[2]);
            }
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