#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& R) : _handlerFactory(R)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& R)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& R)
{
	return RequestResult();
}
