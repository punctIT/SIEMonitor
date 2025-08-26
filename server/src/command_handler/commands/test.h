#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include <thread>
#include "../../utils/ProtocolHandler.h"

class Test : public ProtocolHandler{
    public:
        void write_e(int fd){
            for(int i=0;i<10;i++){
                std::string msg="test ";
                msg+=char('0'+i);
                int e=write(fd,msg.c_str(),msg.size());
                if( e < 0){
                    throw std::runtime_error("Write to client , error");
                }
                sleep(1);
            }
        }
        void test(int fd){
            std::thread t1(&Test::write_e,this,fd);
            t1.detach();
        }
};