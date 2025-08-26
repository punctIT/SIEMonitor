#pragma once

#include <string>
#include <vector>

class ProtocolHandler{
    protected:
        const std::string invalid_login_username="[login]Incorect username or password";
        const std::string succesful_login="[login]Login Succesul";
        const std::string user_already_connected="[login]Error , user already connected";
        const std::string unautehntificated="[login]Must Login";
        const std::string unexpected_error="error";


        const std::string end_msg="\n\r\n\r";
    public:
        std::string get_text(std::vector<std::string> data){
            std::string out="";
            for(auto i : data){
                out+=i;
                out+=" ";
            }
            return out;
        }

};