#include "OnlineUsers.hpp"

#define in :

OnlineUsers::OnlineUsers(){
    users_db.set_database_path("UserDatabase.db");
}
OnlineUsers& OnlineUsers::set_fd(const int &fd){
    this->fd=fd;
    return *this;
}
OnlineUsers& OnlineUsers::run(){
    const std::string sql = "SELECT username, strftime('%H:%M:%S', timestamp) as time_only FROM Users;";
    auto users=users_db.get_data(sql.c_str());
    auto text=get_text(users,"[USERS]");
    write(fd,text.c_str(),text.size());
    return *this;
}