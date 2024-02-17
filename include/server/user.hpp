#pragma once
#include <string>
#include <folly/String.h>
struct User
{
private:
    int id = -1;
    std::string name = "";
    std::string password = "";
    std::string state = "offline";
    

public:
    void setId(int id) { this->id = id; }
    void setName(std::string const &name) { this->name = name; }
    void setPwd(std::string const &password) { this->password = password; }
    void setState(std::string const &state) { this->state = state; }
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPwd() const { return password; }
    std::string getState() const { return state; }
};