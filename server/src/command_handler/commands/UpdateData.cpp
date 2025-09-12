#include "UpdateData.hpp"

#include <format>


UpdateLogsData::UpdateLogsData(){
    this->logs_db.set_database_path("logsData.db");
}
UpdateLogsData& UpdateLogsData::update_resolved(const std::string id,const std::string status){
    std::string sql = std::format("UPDATE logs SET resolved={} WHERE id = {};",status,id);
    logs_db.run_command(sql.c_str());
    return *this; 
}