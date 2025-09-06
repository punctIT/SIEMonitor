#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>
#include <iostream>
#include <optional>
#include "ClientListener.h"
#include "../../utils/SplitText.h"
#include "../../command_handler/CommandHandler.h"

#define in :

ClientListener::ClientListener(){
    std::cout<<"ClientListenerServer start"<<std::endl;
    try{
        auth.set_password_db("Password.db");
    }
    catch (std::exception &e) {
        std::cout<<e.what()<<std::endl;
        exit(2);
    }
    
}
ClientListener& ClientListener::set_port(const int port){
    this->port=port;
    return *this;
}
ClientListener& ClientListener::server_configure(){
    struct sockaddr_in server_addr;
    // Create Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("Error socket");
    }

    // Set server adress
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(this->port);

    // 3. Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Error bind");
    }

    // 4. Listen for conextions
    if (listen(server_fd, 1) < 0) {
        throw std::runtime_error("Error listen ");
    }
    return *this;
}
void ClientListener::send_receive(const int client_fd){
    const int buffer_size=1024;
    char buffer[buffer_size];
    std::optional<std::string> username=std::nullopt;
    HandleCommand cmd;
    std::string recvBuffer;
    while(true){
        int bytes_read = read(client_fd, buffer, buffer_size - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            recvBuffer.append(buffer, bytes_read);
            size_t pos;
            while ((pos = recvBuffer.find("\n\r")) != std::string::npos) {
                std::string input_str = recvBuffer.substr(0, pos);
                recvBuffer.erase(0, pos + 2);
                std::cout<<input_str<<std::endl;
                SplitTest input(input_str);
                auto args=input.get_splited();
                // for(auto i in args){
                //     std::cout<<'['<<i<<"]\n";
                // }
                if (username.has_value()){
                    try{
                        cmd.run(args);
                    }
                    catch (std::exception &e){
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else {
                    if(args[0]=="login" &&args.size() >=3){
                        username=auth.check_login(args[1],args[2]);
                        if(username.has_value()){
                            username=auth.check_online_status(args[1]);
                            if(username.has_value()){
                                write(client_fd,succesful_login.c_str(),succesful_login.size());
                                cmd.set_file_descriptor(client_fd)
                                .set_username(args[2]); 
                            }
                            else {
                                write(client_fd,user_already_connected.c_str(),user_already_connected.size());
                            }
                        }
                        else {
                            write(client_fd,invalid_login_username.c_str(),invalid_login_username.size());
                        }
                    }
                    else {
                        write(client_fd,unautehntificated.c_str(),unautehntificated.size());
                    }
                
                }
            }
        } else if (bytes_read == 0) {
            // clientul closes normali

            printf("Client deconectat.\n");
            if(username.has_value()){
                auth.delete_online_user(username.value());
            }
            
            close(client_fd);
            break; 
        } else {
            // read error
            perror("read");
            if(username.has_value()){
                auth.delete_online_user(username.value());
            }
            close(client_fd);
            break;
        }
    }
}
ClientListener& ClientListener::start_listen(){
    printf("Server TCP for clients listen at %d...\n", this->port);
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd;

    while(true){
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept failed");
            continue;
        }

        printf("Client connected!\n");
        std::thread client_thread(&ClientListener::send_receive, this, client_fd);
        client_thread.detach(); 
        
    }
    return *this;
    
    close(server_fd);
}
