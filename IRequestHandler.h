#pragma once

#include <vector>
#include <string>
#include <ctime>
#include "strucrtRequest.h"

class IRequestHandler;


struct RequestResult
{
    Buffer response;
    IRequestHandler* newHandler;
};



class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
    virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};

