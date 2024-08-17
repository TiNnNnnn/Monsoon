#ifndef NET_H
#define NET_H

#include<iostream>
#include<thread>
#include"../../../common/include/channel.hpp"

class Message{
public:
    std::string type_;
    std::string name_;
    std::string from_user_id_;
    std::string to_user_id_;
    std::string content_;
    std::string session_;

    Message(std::string type,std::string name,std::string from_user_id,std::string to_user_id,std::string content,std::string session)
        :type_(type),name_(name),from_user_id_(from_user_id),to_user_id_(to_user_id),content_(content),session_(session)
    {}
};

void sends( Channel<Message>& channel){}

class Connect{
public:
    Connect(std::string svr_addr):
        svr_addr_(svr_addr)
    {}

    void send(Message& data){
        channel.Send(data);
    }

    Message recv(){
        return channel.Receive();
    }

    void close(){
    };
private:
    std::string svr_addr_;
    Channel<Message> channel;   
};

#endif