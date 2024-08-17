#ifndef API_H
#define API_H
#include<string>
#include"net.hpp"

const std::string msg_type_text = "text";

class Chat{
public:
    std::string nick_;
    std::string user_id_;
    std::string session_id_;
    Connect* conn_;

    Chat(std::string svr_addr,std::string nick,std::string use_id,std::string sid)
        :nick_(nick),user_id_(use_id),session_id_(sid)
    {
        conn_ = new Connect(svr_addr);
    }
    void Send(Message &msg){
        conn_->send(msg);
    };
    Message Recv(){
        return conn_->recv();
    }
    void Close(){
        conn_->close();
    }
};



#endif 