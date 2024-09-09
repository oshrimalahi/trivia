#pragma once
#include "IDatabase.h"
#include "sqlite3.h" 



class SqliteDatabase: public IDatabase
{
public:
	int open();
	void close();
	bool doesUserExist(std::string& username);
	bool doesPasswordMatch(std::string& username, std::string& password);
	int addNewUser(std::string& username, std::string& password, std::string mail);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	bool isFile(const std::string& filePath);


	sqlite3* _DB;

};