#pragma once
#include "user.hpp"
class UserModel
{

public:
    bool insert(User &user);
    User query(int id);
    bool updateState(User const& user);
};
