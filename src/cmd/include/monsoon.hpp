#ifndef MONSOON_H
#define MONSOON_H

#include<iostream>
#include<CLI/CLI.hpp>
typedef void (*SubCallBack)(CLI::App *, std::string*);
class Cmd{
public:
    Cmd();
    void Init();
    void Monsoon(CLI::App *cmd, std::string args[]);
    int Execute(int argc,char** argv);
    void InitConfig();
    void AddSubCmd(std::string sub_name,std::string sub_desp,SubCallBack sub_call);

protected:
    CLI::App *root_cmd = nullptr;
};
#endif