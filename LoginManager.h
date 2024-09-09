#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "SqliteDatabase.h"

class LoginManager
{
public:
	int login(std::string& username, std::string& password);
	int signup(std::string& username, std::string& password, std::string& mail);
	int logout(std::string& username);

private:
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};