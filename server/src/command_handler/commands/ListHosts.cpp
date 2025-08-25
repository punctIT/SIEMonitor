#include "ListHosts.hpp"


ListHosts::ListHosts(){
    logs_db.set_database_path("logsData.db");
}
ListHosts& ListHosts::set_fd(const int &fd){
    this->fd=fd;
    return *this;
}
ListHosts& ListHosts::get_hosts(){
    const std::string sql="SELECT DISTINCT hostname from logs;";
    auto hosts=logs_db.get_data(sql.c_str());
    const std::string text = get_text(hosts);
    write(fd,text.c_str(),text.size());
    return *this;
}
ListHosts& ListHosts::get_sources(const std::string &host){
    std::string sql="SELECT DISTINCT source FROM logs WHERE hostname='";
    sql+=host;sql+="';";
    auto hosts=logs_db.get_data(sql.c_str());
    if(hosts.empty()==false){
        const std::string text = get_text(hosts);
        write(fd,text.c_str(),text.size());
    }
    else {
        write(fd,unexpected_error.c_str(),unexpected_error.size());
    }
    return *this;
}