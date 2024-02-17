#include "db.hpp"

MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
    mysql_options(_conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);
}
MySQL::~MySQL()
{
    if (_conn != nullptr)
    {
        mysql_close(_conn);
    }
}
bool MySQL::connect()
{

    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(), passwd.c_str(), dbname.c_str(), port, nullptr, 0);
    if (p != nullptr)
    {
        // mysql_query(_conn, "set names gbk");
        mysql_set_character_set(_conn, "gbk");
        LOG_INFO << "connect mysql success!";
    }
    else
    {
        LOG_INFO << "connect mysql error!\n"<<mysql_error(_conn);
    }

    return p;
}
bool MySQL::update(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << " : " << __LINE__ << " : " << sql << " 更新失败!";
        return false;
    }
    return true;
}
MYSQL_RES *MySQL::query(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << " : " << __LINE__ << " : " << sql << " 查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}
MYSQL *MySQL::getConnection() const
{
    return _conn;
}
