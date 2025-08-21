#include "network/ServerConection.h"

int main() {
    ServerConection server;
    server.set_server_adress("127.0.0.1")
          .set_server_port(12345)
          .configure_connection();
    server.sent_receive();
}