#include "IRequestHandler.h"

// JsonResponsePacketSerializer implementations
Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    nlohmann::json jsonResponse;
    jsonResponse["status"] = response.status;
    return serializeResponse(jsonResponse, MESSAGE_CODE_LOGIN);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    nlohmann::json jsonResponse;
    jsonResponse["status"] = response.status;
    return serializeResponse(jsonResponse, MESSAGE_CODE_SIGNUP);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    nlohmann::json jsonResponse;
    jsonResponse["message"] = response.message;
    return serializeResponse(jsonResponse, MESSAGE_CODE_ERROR);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const nlohmann::json& jsonResponse, Byte messageCode)
{
    std::string jsonString = jsonResponse.dump();
    Buffer buffer;

    buffer.push_back(messageCode);

    unsigned int messageSize = jsonString.size();
    for (int i = 0; i < 4; i++)
    {
        buffer.push_back((messageSize >> (8 * (3 - i))) & 0xFF);
    }

    buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

    return buffer;
}

// JsonRequestPacketDeserializer implementations
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const RequestInfo& requestInfo)
{
    nlohmann::json jsonRequest = deserializeJson(requestInfo.buffer);
    LoginRequest request;
    request.username = jsonRequest["username"];
    request.password = jsonRequest["password"];
    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const RequestInfo& requestInfo)
{
    nlohmann::json jsonRequest = deserializeJson(requestInfo.buffer);
    SignupRequest request;
    request.username = jsonRequest["username"];
    request.password = jsonRequest["password"];
    request.email = jsonRequest["email"];
    return request;
}

nlohmann::json JsonRequestPacketDeserializer::deserializeJson(const Buffer& buffer)
{
    std::string jsonString(buffer.begin() + 5, buffer.end()); // Skip message code and size
    return nlohmann::json::parse(jsonString);
}

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
        auto loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo);
        LoginResponse response{ 1 }; // Assuming success
        RR.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    else if (messageCode == MESSAGE_CODE_SIGNUP)
    {
        auto signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo);
        SignupResponse response{ 1 }; // Assuming success
        RR.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    ErrorResponse errorResponse{ "Invalid request" };
    RR.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
    IRequestHandler* IRH;
    RR.newHandler = IRH;
    return RR;
}