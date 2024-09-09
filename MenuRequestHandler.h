#pragma once
#include "strucrtRequest.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

struct RequestResult;
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory&);
	bool isRequestRelevant(const RequestInfo& requestInfo);
	RequestResult handleRequest(const RequestInfo& requestInfo);
private:
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

};