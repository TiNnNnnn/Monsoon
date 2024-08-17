#ifndef CUI_H
#define CUI_H

#include "../sdk/inlcude/api.hpp"
#include<iostream>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <thread>

using namespace ftxui;

std::vector<Message> messages;
std::string input_text;
int pos = 0;
auto screen = ScreenInteractive::TerminalOutput();
Chat* chat;

void viewPrint(const Message& msg, bool newline = true) {
    std::string output = msg.name_ + ": " + msg.content_;
    if (newline) {
        output += "\n";
    }
    messages.push_back(msg);
    screen.PostEvent(Event::Custom);
}

void doRecv() {
    while (true) {
        auto msg = chat->Recv();  // 阻塞调用接收消息
        viewPrint(msg, true);
    }
}

void sendMessage() {
    if (!input_text.empty()) {
        Message msg("msg", "yyk", "1", "2", input_text, "111");
        viewPrint(msg, true);
        chat->Send(msg);
        input_text.clear();
    }
}

Element viewOutput() {
    Elements elements;
    for (const auto& msg : messages) {
        elements.push_back(text(msg.name_ + ": "+ msg.content_));
    }
    return window(text("Messages"), vbox(std::move(elements)) | frame | vscroll_indicator | flex);
}


// 构建用户界面
Component BuildUI() {
    InputOption opt;
    opt.multiline = true;
    opt.cursor_position = 0;
    auto input = Input(&input_text, "Type your message here",opt);

    auto send_button = Button("Send", [&] {
        sendMessage();
    },ButtonOption::Ascii());

    auto chat_box = Renderer([&] {
        return viewOutput();
    });
    
    auto component = Container::Vertical({
        chat_box,input,send_button
    });


    auto renderer =  Renderer(component,[&] {
        return vbox({
            window(text("Monsoon"), text("开始聊天了!")),
            hbox(chat_box->Render())| size(HEIGHT,EQUAL,10) | hscroll_indicator,
            hbox({
                hbox(input->Render() |size(WIDTH, EQUAL, 50)) | size(HEIGHT,GREATER_THAN,50),
                hbox(send_button->Render() | color(Color::Green1) | size(WIDTH, GREATER_THAN, 5))
            }) | border | size(HEIGHT, EQUAL, 3),
            //container->Render() | vscroll_indicator | frame |size(HEIGHT, LESS_THAN, 10) | border
        });
    });
    screen.Loop(renderer);
}

// 主函数运行 UI
void Runmain() {
    chat = new Chat("127.0.0.1:8080","tinn","1","1");
    // 启动接收消息线程
    std::thread recv_thread(doRecv);
    std::cout << "begin recv thread" << std::endl;

    auto component = BuildUI();

    // 等待接收线程结束
    recv_thread.join();

    delete chat;
}

#endif



