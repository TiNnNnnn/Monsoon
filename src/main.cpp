#include"cmd/include/monsoon.hpp"
#include"cmd/include/client.hpp"

int main(int argc,char** argv){
    Cmd r_cmd;
    ClientCmd c_cmd;
    
    c_cmd.Register(&r_cmd);
    r_cmd.Execute(argc,argv);
}

