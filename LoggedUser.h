#pragma once
#include <string>
class LoggedUser
{
public:
	void setUserName(std::string username);
	std::string getUserName() const { return _username; };
	bool operator==(const LoggedUser& other);

private:
	std::string _username;
};