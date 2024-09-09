#pragma once

#include <vector>
#include <string>
#include <ctime>
#include "json.hpp"

using Byte = unsigned char;
using Buffer = std::vector<Byte>;

const Byte MESSAGE_CODE_LOGIN = 1;
const Byte MESSAGE_CODE_SIGNUP = 2;
const Byte MESSAGE_CODE_ERROR = 3;

// Response structures
struct LoginResponse { unsigned int status; };
struct SignupResponse { unsigned int status; };
struct ErrorResponse { std::string message; };
struct RequestResult;

// Request structures
struct LoginRequest
{
    std::string username;
    std::string password;
};
struct SignupRequest
{
    std::string username;
    std::string password;
    std::string email;
};
struct RequestInfo
{
    int id;
    std::time_t receivalTime;
    Buffer buffer;
};

class JsonResponsePacketSerializer
{
public:
    static Buffer serializeResponse(const LoginResponse& response);
    static Buffer serializeResponse(const SignupResponse& response);
    static Buffer serializeResponse(const ErrorResponse& response);

private:
    static Buffer serializeResponse(const nlohmann::json& jsonResponse, Byte messageCode);
};

class JsonRequestPacketDeserializer
{
public:
    static LoginRequest deserializeLoginRequest(const RequestInfo& requestInfo);
    static SignupRequest deserializeSignupRequest(const RequestInfo& requestInfo);

private:
    static nlohmann::json deserializeJson(const Buffer& buffer);
};

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
    virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};

struct RequestResult
{
    Buffer response;
    IRequestHandler* newHandler;
};

class LoginRequestHandler : public IRequestHandler {
public:
    LoginRequestHandler() = default;
    ~LoginRequestHandler() override = default;

    bool isRequestRelevant(const RequestInfo& requestInfo) override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;
};