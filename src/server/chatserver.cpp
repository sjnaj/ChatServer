#include "chatserver.hpp"
#include "chatservice.hpp"
#include <functional>
#include <string>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std::placeholders;

ChatServer::ChatServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr, const std::string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setThreadNum(4);
}

void ChatServer::start() { _server.start(); }

void ChatServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown();
    }
}
void ChatServer::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp time)
{
    auto buf = buffer->retrieveAllAsString();
    auto js = json::parse(buf);
    auto handler = ChatService::instance()->getHandler(js["msgid"].get<EnMsgType>());
    handler(conn, js, time);
}
