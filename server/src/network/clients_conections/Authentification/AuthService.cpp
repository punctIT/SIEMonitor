#include "AuthService.h"
#include <sqlite3.h>
#include <iostream>
#include <filesystem>

AuthService::AuthService(){
    int rc = sqlite3_open("logsData.db", &this->active_users_db);

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "Name Text,"
        "timestamp DATETIME,"
        ");";

    char *errMsg = 0;
    rc = sqlite3_exec(this->active_users_db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Create table error " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } 

}
AuthService&  AuthService::set_password_db(std::string path){
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("FATAL ERROR , Users Database path is invalid");  
    } 
    if (sqlite3_open(path.c_str(), &this->password_db) != SQLITE_OK) {
        throw std::runtime_error("FATAL ERROR , can't open User Database");   
    }
    return *this;
}
bool AuthService::check_login(std::string username,std::string password){
    return true;
}