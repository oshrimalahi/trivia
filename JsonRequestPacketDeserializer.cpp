#include "JsonRequestPacketDeserializer.h"


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
