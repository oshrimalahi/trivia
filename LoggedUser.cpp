#include "LoggedUser.h"

void LoggedUser::setUserName(std::string username)
{
    _username = username;
}

bool LoggedUser::operator==(const LoggedUser& other)
{
    return getUserName() == other.getUserName();
}
