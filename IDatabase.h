#pragma once
#include <string>

class IDatabase
{
public:
	int virtual open() = 0;
	void virtual close() = 0;
	bool virtual doesUserExist(std::string) = 0;
	bool virtual doesPasswordMatch(std::string, std::string) = 0;
	int virtual addNewUser(std::string, std::string, std::string) = 0;
};