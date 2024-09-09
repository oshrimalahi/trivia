#pragma once
#include "json.hpp"
#include "strucrtRequest.h"
#include "structsResponse.h"

using Byte = unsigned char;

using Buffer = std::vector<Byte>;

struct RequestInfo;

class JsonRequestPacketDeserializer
{
public:
    static LoginRequest deserializeLoginRequest(const RequestInfo& requestInfo);
    static SignupRequest deserializeSignupRequest(const RequestInfo& requestInfo);

private:
    static nlohmann::json deserializeJson(const Buffer& buffer);
};