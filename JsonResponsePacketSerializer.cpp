#include "JsonResponsePacketSerializer.h"
using Byte = unsigned char;

const Byte MESSAGE_CODE_LOGIN = 1;
const Byte MESSAGE_CODE_SIGNUP = 2;
const Byte MESSAGE_CODE_ERROR = 3;

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

