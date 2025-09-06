#pragma once

#include <string>
#include <vector>
#include <format>

class ProtocolHandler{
    protected:
        const std::string invalid_login_username="[login]Incorect username or password\n\r\n\r";
        const std::string succesful_login="[login]Login Succesul\n\r\n\r";
        const std::string user_already_connected="[login]Error , user already connected\n\r\n\r";
        const std::string unautehntificated="[login]Must Login\n\r\n\r";
        const std::string unexpected_error="error\n\r\n\r";


        const std::string end_msg="\n\r\n\r";
    public:
        std::string get_text(std::vector<std::string> data){
            std::string out="";
            for(auto i : data){
                out+=i;
                out+=" ";
            }
            return out+end_msg;
        }
        std::string log_text_protocol(std::string data,std::string type,const std::string specifit_type=""){
            while(type.size()<=8)
                type+='0';
                
            if (specifit_type.empty())
                return "[LOG]"+std::format("[{}]",type)+data+end_msg;
            else return "[LOG]"+std::format("[{}][{}]",type,specifit_type)+data+end_msg;
        }

};