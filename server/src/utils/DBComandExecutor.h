#pragma once 
#include <sqlite3.h>
#include <string>
#include <vector>
#include <filesystem>
#include <shared_mutex>
#include <mutex>

class DBComandExecutor{
    private:
        sqlite3* db;
        int rc;
        std::string path;
        std::shared_mutex db_rwmutex;//is inspired from RUST [RWLOCK which is much better ]
        //is it use for db , more readers , one modifiy
    public:
        DBComandExecutor(){
           
        }
        ~DBComandExecutor() {
            if (db) {
                sqlite3_close(db);
            }
        }
        //this function is use for set an existing database 
        //for example , Password DataBase
        DBComandExecutor& set_database_path(std::string path){
            std::unique_lock lock(db_rwmutex);
            this->path=path;
            if (!std::filesystem::exists(path)) {
                throw std::runtime_error("FATAL ERROR ,Database path is invalid");  
            } 
            if ((rc=sqlite3_open(path.c_str(), &db)) != SQLITE_OK) {
                throw std::runtime_error("FATAL ERROR , can't open Database");   
            }
            sqlite3_close(db);
            return *this;
        }
        //this function is to create a new database
        DBComandExecutor& set_new_database_path(std::string path){
            std::unique_lock lock(db_rwmutex);
            this->path=path;
            if ((rc=sqlite3_open(path.c_str(), &db)) != SQLITE_OK) {
                throw std::runtime_error("FATAL ERROR , can't open Database");   
            }
            sqlite3_close(db);
            return *this;
        }
        static int callback(void* data, int argc, char** argv, char** colName) {
            auto* results = reinterpret_cast<std::vector<std::string>*>(data);

            std::string row;
            for (int i = 0; i < argc; i++) {
                row += (argv[i] ? argv[i] : "NULL");
                if (i < argc - 1) row += " "; 
            }

            results->push_back(row);
            return 0;
        }
        std::vector<std::string> get_data(const char *cmd){
            std::shared_lock lock(db_rwmutex);
            if ((rc=sqlite3_open(path.c_str(), &db)) != SQLITE_OK) {
                throw std::runtime_error("FATAL ERROR , can't open Database");   
            }
            std::vector<std::string> rows;
            char *errMsg=0;
            rc = sqlite3_exec(db, cmd, callback, &rows, &errMsg);
            if (rc != SQLITE_OK) {
                std::string error = "SQL error: ";
                if (errMsg) {
                    error += errMsg;
                    sqlite3_free(errMsg); 
                }
                throw std::runtime_error(error);
            }
            sqlite3_close(db);
            return rows;
        }
        DBComandExecutor& run_command(const char* cmd){
            std::unique_lock lock(db_rwmutex);
            if ((rc=sqlite3_open(path.c_str(), &db)) != SQLITE_OK) {
                throw std::runtime_error("FATAL ERROR , can't open Database");   
            }
            char *errMsg=0;
            rc = sqlite3_exec(db, cmd,0,0 ,&errMsg);
            if (rc != SQLITE_OK) {
                std::string error = "SQL error: ";
                if (errMsg) {
                    error += errMsg;
                    sqlite3_free(errMsg); 
                }
                throw std::runtime_error(error);
            }
            sqlite3_close(db);
            return *this;
        }
};