#pragma once 
#include <sqlite3.h>
#include <string>

class AuthService{
    private:
        sqlite3* password_db;
        sqlite3* active_users_db;
    public:
        AuthService();
        AuthService& set_password_db(std::string);
        bool check_login(std::string ,std::string);
};