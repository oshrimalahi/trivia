#pragma once
#include "json.hpp"
#include "structsResponse.h"
using Byte = unsigned char;

using Buffer = std::vector<Byte>;

class JsonResponsePacketSerializer
{
public:
    static Buffer serializeResponse(const LoginResponse& response);
    static Buffer serializeResponse(const SignupResponse& response);
    static Buffer serializeResponse(const ErrorResponse& response);

private:
    static Buffer serializeResponse(const nlohmann::json& jsonResponse, Byte messageCode);
};
