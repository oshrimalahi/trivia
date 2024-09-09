#pragma once
#include <vector>
#include <string>
#include "RoomData.h"
#include "LoggedUser.h"
class Room
{
public:
	Room() = default;
	Room(const RoomData& data);
	~Room();
	void addUser(LoggedUser& user);
	void removeUser(LoggedUser& user);
	RoomData getMetaData() const;
	std::vector<std::string> getAllUsers();




private:
	RoomData _metadata;
	std::vector<LoggedUser> _users;

};