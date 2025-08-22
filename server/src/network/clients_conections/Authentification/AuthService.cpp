#include "AuthService.h"
#include <sqlite3.h>
#include <iostream>
#include <filesystem>

AuthService::AuthService(){
   
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "Name Text,"
        "timestamp DATETIME,"
        ");";

    try{
         this->active_users_db.set_new_database_path("UserDatabase.db")
                         .run_command(sql);
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }

}
AuthService&  AuthService::set_password_db(std::string path){
    try{
         this->password_db.set_database_path("Password.db");                    
    }
    catch (std:: exception&e){
        std::cout<<e.what()<<std::endl;
    }
    return *this;
}
bool AuthService::check_login(std::string username,std::string password){
    return true;
}