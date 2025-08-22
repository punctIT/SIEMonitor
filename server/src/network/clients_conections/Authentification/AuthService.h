#pragma once 

#include <sqlite3.h>
#include <string>
#include "../../../utils/DBComandExecutor.h"
class AuthService{
    private:
        DBComandExecutor password_db;
        DBComandExecutor active_users_db;
    public:
        AuthService();
        AuthService& set_password_db(std::string);
        bool check_login(std::string ,std::string);
};