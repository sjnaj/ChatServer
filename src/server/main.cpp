#include "chatserver.hpp"
#include <iostream>

int main()
{
    EventLoop loop;
    auto addr = InetAddress{"127.0.0.1", 8888};
    auto server = ChatServer{&loop, addr, "ChatServer"};
    server.start();
    loop.loop();
}