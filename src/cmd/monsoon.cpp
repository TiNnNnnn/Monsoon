#include "include/monsoon.hpp"

Cmd::Cmd(){
    root_cmd = new CLI::App("a distributed instant message system","Monsoon");
    root_cmd->callback([&](){Monsoon(root_cmd,nullptr);});
}

//Nothing to do
void Cmd::Init(){}

void Cmd::Monsoon(CLI::App *cmd, std::string args[]){
    //std::cout<<"you need add some arg behind"<<std::endl;
}

int  Cmd::Execute(int argc,char** argv){
        try { 
            root_cmd->parse(argc,argv); 
            return 0;
        }catch(const CLI::ParseError &e) { 
            return (root_cmd)->exit(e); 
        }
}

void Cmd::AddSubCmd(std::string sub_name,std::string sub_desp,SubCallBack sub_call){
    auto sub = root_cmd->add_subcommand(sub_name,sub_desp);
    sub->callback([sub_call,this,sub](){sub_call(sub,nullptr);});
}

void  Cmd::InitConfig(){

}