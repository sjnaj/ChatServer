#pragma once
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include "public.hpp"
using namespace muduo;
using namespace net;

class ChatServer
{
private:
    TcpServer _server;
    EventLoop *_loop;
    //连接回调
    void onConnection(TcpConnectionPtr const &conn);
    //读写事件回调
    void onMessage(TcpConnectionPtr const &conn, Buffer *buffer, Timestamp time);

public:
    ChatServer(EventLoop *loop, InetAddress const &listenAddr, std::string const &nameArg);
    void start();
};

