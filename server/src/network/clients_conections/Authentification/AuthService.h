#pragma once 

#include <sqlite3.h>
#include <string>
#include "../../../utils/DBComandExecutor.h"
#include <optional>

class AuthService{
    private:
        DBComandExecutor password_db;
        DBComandExecutor active_users_db;
    public:
        AuthService();
        AuthService& set_password_db(std::string);
        std::optional<std::string>  check_login(std::string ,std::string);
};