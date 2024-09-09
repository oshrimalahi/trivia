#include "LoginRequestHandler.h"


// LoginRequestHandler implementations
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    Byte messageCode = requestInfo.buffer[0];
    return messageCode == MESSAGE_CODE_LOGIN || messageCode == MESSAGE_CODE_SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    RequestResult RR;
    Byte messageCode = requestInfo.buffer[0];
    if (messageCode == MESSAGE_CODE_LOGIN)
    {
        LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo);
        int status = login(loginRequest);
        LoginResponse response{ status }; // Assuming success
        RR.response = JsonResponsePacketSerializer::serializeResponse(response);
        if (status == 1)
            RR.newHandler = _handlerFactory.createMenuRequestHandler();
        else 
        {
            RR.newHandler = _handlerFactory.createLoginRequestHandler();
        }
    }
    else if (messageCode == MESSAGE_CODE_SIGNUP)
    {
        SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo);
        int status = signup(signupRequest);
        SignupResponse response{ status }; // Assuming success
        RR.response =  JsonResponsePacketSerializer::serializeResponse(response);
        if (status == 1)
            RR.newHandler = _handlerFactory.createMenuRequestHandler();
        else
        {
            RR.newHandler = _handlerFactory.createLoginRequestHandler();
        }
    }
    ErrorResponse errorResponse{ "Invalid request" };
    RR.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
    IRequestHandler* IRH;
    RR.newHandler = IRH;
    return RR;
}

int LoginRequestHandler::login(LoginRequest r)
{
    return _handlerFactory.getLoginManager().login(r.username, r.password);
}

int LoginRequestHandler::signup(SignupRequest r)
{
    return _handlerFactory.getLoginManager().signup(r.username, r.password, r.email);
}
