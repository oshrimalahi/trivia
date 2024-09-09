#include "LoginManager.h"

int LoginManager::login(std::string& username, std::string& password)
{
    _database->open();
    LoggedUser newUser;
    newUser.setUserName(username);
    if (_database->doesUserExist(username)) 
    {
        auto it = std::find(_loggedUsers.begin(), _loggedUsers.end(), newUser);
        if (it != _loggedUsers.end())
        {
            return 0;
        }  
        if (_database->doesPasswordMatch(username, password))
        {
            _loggedUsers.push_back(newUser);
            _database->close();
            return 1;
        }
        return 0;
    }
    return 0;
}

int LoginManager::signup(std::string& username, std::string& password, std::string& mail)
{
    _database->open();
    if (_database->doesUserExist(username))
    {
        return 0;
    }
    else 
    {
        _database->addNewUser(username, password, mail);
        LoggedUser newUser;
        newUser.setUserName(username);
        _loggedUsers.push_back(newUser);
        _database->close();
        return 1;
    }
}

int LoginManager::logout(std::string& username)
{
    LoggedUser newUser;
    newUser.setUserName(username);
    auto it = std::find(_loggedUsers.begin(), _loggedUsers.end(), newUser);
    if (it != _loggedUsers.end())
    {
        _loggedUsers.erase(it);
        return 1;
    }
    else
    {
    return 0;// not exsit user
    }
}
