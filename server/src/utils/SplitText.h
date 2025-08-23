#pragma once 
#include <vector>
#include <string>
#include <iostream>
#define in :

class SplitTest{
    private:
        std::string input;
    public:
        SplitTest(std::string input){
            this->input=input;
        }
        std::vector<std::string> get_splited(){
            int i=0;
            while(input[i]==' ')
                i+=1;
            std::vector<std::string> args;
            std::string arg="";
            while(i<=input.size()){
                if(input[i]==' '){
                    args.push_back(arg);
                    arg="";
                    while((input[i]==' ') and i<=input.size()){
                        ++i;
                    }
                    continue;
                }
                else {
                    arg+=input[i];
                }
                ++i;
            }
            //3 HOURS FOR THIS SHIT
            //IN RUST IS BETTER < IS  A FUNCTION SPLIT_WHITESPACE <<<< I DONT HAVE TO DEBUG \r\n <
            //3 HOURS OF MY LIFE < C++ GO TO HELL
            //THIS IS THE LAST PROJECT I WILL WRITE IN C++
            if(arg.empty()==false){
                arg.pop_back();
                // for (auto i in arg){
                //     printf("[%d]",i);
                // }
                // std::cout<<std::endl;
                if(arg.size()>2&&arg[arg.size()-1]=='\n'&&arg[arg.size()-2]=='\r')//for windows cli
                    args.push_back(arg.substr(0, arg.size() - 2));
                else if(arg.size()>1&&arg[arg.size()-1]=='\n')//for linux CLI
                    args.push_back(arg.substr(0, arg.size() - 1));
                else {
                    args.push_back(arg);
                }
                // for (auto i in args[args.size()-1]){
                //     printf("[%d]",i);
                // }
                // std::cout<<std::endl;
            }
            // for(auto i in args ){
            //     std::cout<<i<<"] \n";
            // }
            return args;
        }


};