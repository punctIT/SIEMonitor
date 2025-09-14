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
        std::string get_text(std::vector<std::string> data,std::string type,std::string second_type=""){
            std::string out="";
            for(auto i : data){
                out+=i;
                out+=" ";
            }
            if (second_type.empty())    
                return type+out+end_msg;
            else return type+second_type+out+end_msg;
        }
        std::string get_error(const std::string s){
            return s+end_msg;
        }
        std::string log_text_protocol(std::string data,std::string type){                
            return "[LOG]"+std::format("[{}]",type)+data+end_msg;
           
        }
        std::string severity_text_protocol(std::string data,std::string type){

            return "[INC]"+std::format("[{}]",type)+data+end_msg;
          
        }


};