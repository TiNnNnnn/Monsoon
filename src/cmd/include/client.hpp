#ifndef CLIENT_H
#define CLINET_H

#include "monsoon.hpp"
#include "../../client/include/cui.hpp"

class ClientCmd{
public:
    void Register(Cmd*cmd){
        cmd->AddSubCmd("client","im client",ClientHandle);
    }
    static void ClientHandle(CLI::App* cmd, std::string args[]){
        Runmain();
    }
};




#endif