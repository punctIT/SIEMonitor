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
        AuthService& set_password_db(const std::string);
        std::optional<std::string>  check_login(const std::string ,const std::string);
        std::optional<std::string> check_online_status(const std::string);
        void delete_online_user(const std::string);
};