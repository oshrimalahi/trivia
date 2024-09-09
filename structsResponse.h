#pragma once
#include "Room.h"

#include <vector>


using Byte = unsigned char;
using Buffer = std::vector<Byte>;

struct LoginResponse { unsigned int status; };
struct SignupResponse { unsigned int status; };
struct ErrorResponse { std::string message; };

struct LogoutResponse
{
public:
	unsigned int status;
};
struct GetRoomsResponse
{
public:
	unsigned int status;
	std::vector<RoomData> rooms;

};

struct GetPlayersInRoomResponse
{
public:
	std::vector<std::string> players;

};

struct getHighScoreResponse
{
public:
	unsigned int status;
	std::vector<std::string> statistics;
};

struct getPersonalStatsResponse
{
public:
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse
{
public:
	unsigned int status;
};

struct CreateRoomResponse
{
public:
	unsigned int status;
};
