#include "ListHosts.hpp"

#include <format>
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

    const std::string text = get_text(hosts,"[HOSTS]");
    write(fd,text.c_str(),text.size());
    return *this;
}
ListHosts& ListHosts::get_sources(const std::string &host){
    const std::string sql=std::format("SELECT DISTINCT source FROM logs WHERE hostname='{}';",
                                       host);
    auto hosts=logs_db.get_data(sql.c_str());
    if(hosts.empty()==false){
        const std::string text = get_text(hosts,"[SOURCES]");
        write(fd,text.c_str(),text.size());
    }
    else {
        write(fd,unexpected_error.c_str(),unexpected_error.size());
    }
    return *this;
}