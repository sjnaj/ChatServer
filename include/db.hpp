#pragma once

#include <muduo/base/Logging.h>
#include <mysql/mysql.h>
#include <string>
class MySQL
{
public:
    MySQL();
    ~MySQL();
    bool connect();
    bool update(std::string sql);
    MYSQL_RES *query(std::string sql);
    MYSQL *getConnection() const;

private:
    MYSQL *_conn;
    // inline static std::string server = "localhost";
    inline static std::string server = "172.20.47.36";//“127.0.0.1”会解析超时

    inline static std::string user = "root";
    inline static std::string passwd = "fengsc2017";
    inline static std::string dbname = "chat";
    inline static int port = 8888;
    inline static int timeout = 10;
};