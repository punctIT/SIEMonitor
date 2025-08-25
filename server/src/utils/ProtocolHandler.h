#pragma once

#include <string>
#include <vector>

class ProtocolHandler{
    protected:
        const std::string invalid_login_username="Incorect username or password";
        const std::string succesful_login="Login Succesul";
        const std::string user_already_connected="Error , user already connected";
        const std::string unautehntificated="Must Login";
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