#pragma once
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Logging.h>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>
#include <folly/AtomicHashMap.h>
#include "public.hpp"
#include "userModel.hpp"
using namespace muduo;
using namespace net;
using json = nlohmann::json;
using MsgHandler = std::function<void(TcpConnectionPtr const &conn, json &js, Timestamp time)>;
// 业务类
class ChatService
{
public:
    static ChatService *instance();
    void login(TcpConnectionPtr const &conn, json &js, Timestamp time);
    void reg(TcpConnectionPtr const &conn, json &js, Timestamp time);

    MsgHandler getHandler(EnMsgType msgid);

private:
    ChatService();
    std::unordered_map<EnMsgType, MsgHandler> _msgHandlerMap;
    // folly::AtomicHashMap<int, TcpConnectionPtr> _connMap;
    UserModel _userModel;
};