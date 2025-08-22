#include "LogDatabaseWriter.h"
#include <iostream>
#include <sstream>

#include <chrono>
#include <ctime>

LogDatabaseWriter::LogDatabaseWriter(){
    std::cout<<"Start writing log in DataBase"<<std::endl;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS logs("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "pri INT,"
        "timestamp DATETIME,"
        "hostname TEXT,"
        "source TEXT,"
        "severity TEXT,"
        "message TEXT"
        ");";
    db.set_new_database_path("logsData.db")
      .run_command(sql);
}
LogDatabaseWriter& LogDatabaseWriter::set_thread_safe_quere(ThreadSafeQueue <std::string>* queue){
    this->queue=queue;
    return *this;
}

std::string get_date(std::string month,std::string day,std::string time){
    std::vector<std::string> months = { 
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    for(int i=0;i<months.size();++i){
        if (months[i]==month){
            //get current YEAR
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm tm = *std::localtime(&t);
            std::string year= std::to_string(tm.tm_year + 1900); 
            //create standard SQL datetime formmat YYYY:MM:DD HH:HH:HH
            std::string result=year+"-"+std::to_string(i + 1)+"-"+day+" "+time;
            return result;
        }
    }
    return "";
}
//this function gets the entire log , splited , by format
//<PRI>TIMESTAMP HOSTNAME ... MESSAGE
std::vector<std::string> get_splited_log(std::string log){

    std::vector<std::string> logs;
    
    std::string word="";
    int c=0;
    while (log[c] != '>' and c < 10){
        if(isdigit(log[c])){
            word+=log[c];
        }  
        c+=1;
    }
    //PRI
    logs.push_back(word);
    log.erase(0,c+1);
    c=0;
    std::istringstream iss(log);
    int count = 0;
    //next 4 MOUNTH DAY TIME HOSTNAME ...
    while (count < 5 && iss >> word) {
        logs.push_back(word);
        c+=(1+word.length());
        count++;
    }
    //MESSAGE
    std::streampos pos = iss.tellg();
    if (pos != -1) {
        std::string rest = log.substr(pos);
        logs.push_back(rest);
    } else {
        logs.push_back("");
    }
    return logs;
}
//severity on a scale from 0 to 7
std::string get_severity(int pri){
    std::vector<std::string> severity = { 
        "Emergency","Alert","Critical","Error","Warning","Notice","Informational","Debug"
    };
    return severity[pri%8];
}
//this function retund a valid SQL insert command
//or ""-NOne in case something went wrotg , like 
// - invalid syslog format
// - incomplete syslog
std::string get_sql_command(std::vector <std::string> logs){
    if(logs.size() < 7) {
        std::cerr << "ERROR: Not enough log elements, got " << logs.size() << std::endl;
        return "";
    }
    //the case when there is no <PRI>, or is invalid format
    if(logs[0].empty()) {
        std::cerr << "ERROR: Invalid priority: '" << logs[0] << "'" << std::endl;
        return "";
    }
    
    int priority = stoi(logs[0]);
    //for optimization ,  for DB,
    std::string severity=get_severity(priority);
    if (logs[6].find("heartbeat") != std::string::npos ){
        return "";
    }

    //for a valid message , in case of ' character
    std::string escaped;
    for(char c : logs[6]){
        if(c == '\'') escaped += "''";
        else escaped += c;
    }
    
    std::string sql = "INSERT INTO logs(pri, timestamp, hostname, source, severity, message) VALUES (" +
                  logs[0] + ", '" + get_date(logs[1],logs[2],logs[3]) + "', '" +
                  logs[4] + "', '" + logs[5] + "', '" + 
                  severity + "', '" + escaped + "');";

    return sql;
}

//this function get the SQL command for log (if is posible) and write it in the database
void LogDatabaseWriter::write_logs(int number){
    //open the database (for each thread is a diferent connection)
    while(true){
        //wait until is something in the queue
        auto log_data=this->queue->pop();
        if (log_data.has_value()){
            auto logs = get_splited_log(log_data.value());
            auto insert_sql=get_sql_command(logs);
            //if 'insert_sql' is empty it's means the log format is invalid , or other error ocured
            if (insert_sql.empty()){
                continue;
            }
            //try to insert log in database
            try{
                this->db.run_command(insert_sql.c_str());
            }
             catch (const std::exception& e) {
                std::cout<<e.what()<<std::endl;
             }
        }
    }
}