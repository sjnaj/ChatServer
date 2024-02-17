
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
using namespace muduo::net;
using namespace muduo;
using namespace std::placeholders;
class ChatServer
{
private:
    TcpServer _server;
    EventLoop *_loop;
    void onConnection(TcpConnectionPtr const &conn)
    {
        if (conn->connected())
        {
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " online" << std::endl;
        }
        else
        {
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " offline" << std::endl;
            conn->shutdown();
        }
    }
    void onMessage(TcpConnectionPtr const &conn, Buffer *buffer, Timestamp time)
    {
        auto buf=buffer->retrieveAllAsString();
        std::cout << "recv data:" << buf<< "time:" << time.toString() << std::endl;
        conn->send(buf);

    }

public:
    ChatServer(EventLoop *loop, InetAddress const &listenAddr, std::string const &nameArg)
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
        _server.setThreadNum(4);
    }
    void start()
    {
        _server.start();
    }
};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 8888);
    ChatServer server(&loop, addr, "ChatSerer");
    server.start();
    loop.loop();

    //sudo tcpdump -i lo -nnn tcp port 8888 -v
}