#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>
#include <iostream>
#include "ClientListener.h"


ClientListener::ClientListener(){
    std::cout<<"ClientListenerServer start"<<std::endl;
    auth.set_password_db("Password.db");
}
ClientListener& ClientListener::set_port(int port){
    this->port=port;
    return *this;
}
void ClientListener::server_configure(){
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
}
void ClientListener::send_receive(int client_fd){
    const int buffer_size=1024;
    char buffer[buffer_size];
    while(true){
        int bytes_read = read(client_fd, buffer, buffer_size - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Am primit: %s\n", buffer);
        } else if (bytes_read == 0) {
            // clientul s-a închis normal
            printf("Client deconectat.\n");
            close(client_fd);
            break; // iesim din bucla clientului
        } else {
            // eroare la read
            perror("read");
            close(client_fd);
            break;
        }
    }
}
void ClientListener::start_listen(){
    printf("Server TCP ascultă pe portul %d...\n", this->port);
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
    
    
    close(server_fd);
}
