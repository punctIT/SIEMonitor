#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>


class ServerConection;

class UpdateWorker : public QObject {
    Q_OBJECT

public:
    UpdateWorker(ServerConection* parent = nullptr,int fd=-1) : SvCon(parent), server_fd(fd) {}
public slots:
    void doWork() {
        char buffer[1024];
        std::string recvBuffer;
        while (true) {
            int bytes = read(server_fd, buffer, sizeof(buffer) - 1);
            if (bytes <= 0) {
                std::cerr << "Connection closed or error\n";
                exit(0);
            }

            buffer[bytes] = '\0';
            recvBuffer.append(buffer, bytes);
            size_t pos;
            while ((pos = recvBuffer.find("\n\r\n\r")) != std::string::npos) {
                std::string message = recvBuffer.substr(0, pos);
                //std::cout<<message<<std::endl;
                QString msg = QString::fromUtf8(message);
                emit updateRequested(msg);
                recvBuffer.erase(0, pos + 4);
            }
           
        }
      
    }
signals:
    void updateRequested(const QString& now);
    

private:
    ServerConection* SvCon;
    int server_fd;
};
