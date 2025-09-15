#include "AuthService.h"
#include <sqlite3.h>
#include <iostream>
#include <filesystem>
#include <optional>
#include <format>
#include "BCrypt.h"

#define in :

AuthService::AuthService(){
   
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Users("
        "username Text,"
        "timestamp DATETIME"
        ");";

    try{
         this->active_users_db.set_new_database_path("UserDatabase.db")
                              .run_command(sql);
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }

}
AuthService&  AuthService::set_password_db(const std::string path){
    try{
         this->password_db.set_database_path(path);                    
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }
    return *this;
}
std::optional<std::string> AuthService::check_login(const std::string username,const std::string password){
    try{
        Bcrypt crypt;
        const std::string sql=std::format("SELECT password FROM Users WHERE username='{}';",
                                    username);
        auto status=password_db.get_data(sql.c_str());
        if(status.size()!=0 and crypt.checkPassword(password,status[0])){
            return username;
        }  
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }
    return std::nullopt;
}
 std::optional<std::string> AuthService::check_online_status(const std::string username){
     try{
        Bcrypt crypt;
        const std::string sql=std::format("SELECT * FROM Users WHERE username='{}';",
                                    username);
        auto status=this->active_users_db.get_data(sql.c_str());
        if(status.empty()){
            const std::string sql2 = std::format("INSERT INTO Users (username, timestamp) VALUES ('{}',datetime('now'));",
                                                 username); 
            active_users_db.run_command(sql2.c_str());
            return username;
        }  
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }
    return std::nullopt;
 }
 void AuthService::delete_online_user(const std::string username){
    std::string sql = std::format("DELETE FROM Users WHERE username='{}';",
                                  username );
    active_users_db.get_data(sql.c_str());
 }