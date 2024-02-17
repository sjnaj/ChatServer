#include "chatservice.hpp"

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

ChatService::ChatService()
{
    _msgHandlerMap.insert({EnMsgType::LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({EnMsgType::REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}
MsgHandler ChatService::getHandler(EnMsgType msgid)
{
    if (!_msgHandlerMap.count(msgid))
    {
        return [=](TcpConnectionPtr const &conn, json &js, Timestamp time)
        {
            LOG_ERROR << "msgid: " << static_cast<int>(msgid) << " can not find handler!\n";
        };
    }

    return _msgHandlerMap[msgid];
}
void ChatService::login(TcpConnectionPtr const &conn, json &js, Timestamp time)
{
    int id = js["id"];
    std::string pwd = js["password"];
    User user = _userModel.query(id);
    json response;
    response["msgid"] = EnMsgType::LOGIN_MSG_ACK;
    if (user.getId() == id && user.getPwd() == pwd)
    {
        if (user.getState() == "online")
        {
            response["errno"] = 2;
            response["errmsg"] = "该账号已经登录，请重新输入新账号";
        }
        else
        {
            user.setState("online");
            _userModel.updateState(user);
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();
        }
    }
    else
    {
        response["errno"] = 1;
        response["errmsg"] = "用户名或者密码错误";
    }
    conn->send(response.dump());
}

void ChatService::reg(TcpConnectionPtr const &conn, json &js, Timestamp time)
{

    auto name = js["name"].get<std::string>();
    auto password = js["password"].get<std::string>();
    User user;
    user.setName(name);
    user.setPwd(password);
    bool state = _userModel.insert(user);
    json response;
    response["msgid"] = EnMsgType::REG_MSG_ACK;
    response["id"] = user.getId();
    response["errno"] = state ? 0 : 1;
    LOG_INFO << response.dump();
    conn->send(response.dump());
}