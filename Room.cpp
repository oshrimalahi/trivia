#include "Room.h"

Room::Room(const RoomData& data) : _metadata(data)
{
}

Room::~Room()
{
}

void Room::addUser(LoggedUser& user)
{
	_users.push_back(user);
}

void Room::removeUser(LoggedUser& user)
{
	auto it = std::find(_users.begin(), _users.end(), user);
	if (it != _users.end()) {
		_users.erase(it);
	}
}

RoomData Room::getMetaData() const
{
	return _metadata;
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> usernames;
	for (const auto& user : _users) {
		usernames.push_back(user.getUserName());
	}
	return usernames;
}
