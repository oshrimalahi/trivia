#include "RoomManagar.h"

RoomManager::RoomManager()
{
	
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser& user, RoomData& roomData)
{
	Room newRoom(roomData);
	newRoom.addUser(user);
}

void RoomManager::deleteRoom(int roomNumber)
{
	_rooms.erase(roomNumber);
}

unsigned int RoomManager::getRoomState(int roomNumber)
{
	if (_rooms.find(roomNumber) != _rooms.end()) {
		return _rooms[roomNumber].getMetaData().isActive ? 1 : 0;
	}
	return 0;
}

//std::vector<RoomData> RoomManager::getRooms() const
//{
//}

Room& RoomManager::getRoom(int roomNumber)
{
	return _rooms.at(roomNumber);
}
