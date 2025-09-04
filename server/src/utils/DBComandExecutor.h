#pragma once 
#include <sqlite3.h>
#include <string>
#include <vector>
#include <filesystem>
#include <mutex>

class DBComandExecutor{
    private:
        sqlite3* db = nullptr;
        std::string path;
        mutable std::mutex db_mutex;
        
    public:
        DBComandExecutor() = default;
        
        ~DBComandExecutor() {
            std::lock_guard<std::mutex> lock(db_mutex);
            if (db) {
                sqlite3_close(db);
            }
        }
        
        DBComandExecutor& set_database_path(const std::string& db_path) {
            std::lock_guard<std::mutex> lock(db_mutex);
            
            if (db) {
                sqlite3_close(db);
                db = nullptr;
            }
            
            this->path = db_path;
            if (!std::filesystem::exists(path)) {
                throw std::runtime_error("Database path is invalid");  
            }
            
            if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
                throw std::runtime_error("Can't open Database");   
            }
            
                char *errMsg = nullptr;
            sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, &errMsg);
            if (errMsg) {
                sqlite3_free(errMsg);
            }
            
            // Setează timeout pentru lock-uri
            sqlite3_busy_timeout(db, 5000); // 5 secunde timeout
            
            return *this;
        }
        
        DBComandExecutor& set_new_database_path(const std::string& db_path) {
            std::lock_guard<std::mutex> lock(db_mutex);
            
            if (db) {
                sqlite3_close(db);
                db = nullptr;
            }
            
            this->path = db_path;
            
            if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
                throw std::runtime_error("Can't open Database");   
            }
            char *errMsg = nullptr;
            sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, &errMsg);
            if (errMsg) {
                sqlite3_free(errMsg);
            }
            
            sqlite3_busy_timeout(db, 5000);
            
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
        
        std::vector<std::string> get_data(const char *cmd) {
            std::lock_guard<std::mutex> lock(db_mutex);
            
            if (!db) {
                throw std::runtime_error("Database not connected");
            }
            
            std::vector<std::string> rows;
            char *errMsg = nullptr;
            int rc = sqlite3_exec(db, cmd, callback, &rows, &errMsg);
            
            if (rc != SQLITE_OK) {
                std::string error = "SQL error: ";
                if (errMsg) {
                    error += errMsg;
                    sqlite3_free(errMsg); 
                }
                throw std::runtime_error(error);
            }
            
            return rows;
        }
        
        DBComandExecutor& run_command(const char* cmd) {
            std::lock_guard<std::mutex> lock(db_mutex);
            
            if (!db) {
                throw std::runtime_error("Database not connected");
            }
            
            char *errMsg = nullptr;
            int rc = sqlite3_exec(db, cmd, nullptr, nullptr, &errMsg);
            
            if (rc != SQLITE_OK) {
                std::string error = "SQL error: ";
                if (errMsg) {
                    error += errMsg;
                    sqlite3_free(errMsg); 
                }
                throw std::runtime_error(error);
            }
            
            return *this;
        }
};