#pragma once
#include <string>
#include <vector>
#include <ctime>

using Byte = unsigned char;

using Buffer = std::vector<Byte>;
struct RequestInfo
{
	int id;
	std::time_t receivalTime;
	Buffer buffer;
};
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


struct GetPlayersInRoomRequest
{
public:
	unsigned int roomId;
};

struct JoinRoomRequest
{
public:
	unsigned int roomId;
};






struct CreateRoomRequest
{
public:
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};