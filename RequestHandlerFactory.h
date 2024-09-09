#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

class IRequestHandler;
class LoginRequestHandler;
class MenuRequestHandler;


class RequestHandlerFactory
{
public:
	IRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler();

private:
	IDatabase* _database;
	LoginManager _loginManager;

};