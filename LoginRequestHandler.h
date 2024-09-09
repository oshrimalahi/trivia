#pragma once
#include "RequestHandlerFactory.h"
#include "strucrtRequest.h"
#include "structsResponse.h" 
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "IRequestHandler.h"

struct RequestResult;
class RequestHandlerFactory;

using Byte = unsigned char;
const Byte MESSAGE_CODE_LOGIN = 1;
const Byte MESSAGE_CODE_SIGNUP = 2;
const Byte MESSAGE_CODE_ERROR = 3;


class LoginRequestHandler : public IRequestHandler {
public:
    LoginRequestHandler(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory) 
    {
    
    };
    ~LoginRequestHandler() override = default;

    bool isRequestRelevant(const RequestInfo& requestInfo) override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
    int login(LoginRequest);
    int signup(SignupRequest);

    RequestHandlerFactory& _handlerFactory;
};
