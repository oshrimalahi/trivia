#pragma once
#include <vector>
#include <string>
#include <map>
#include "Room.h"
class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void createRoom(LoggedUser& user, RoomData& roomData);
	void deleteRoom(int roomNumber);
	unsigned int getRoomState(int roomNumber);
	std::vector<RoomData> getRooms() const;
	Room& getRoom(int roomNumber);


	unsigned int _roomNumber;
	std::string roomName;
	std::vector<std::string> _activeRooms;
private:
	std::map<unsigned int, Room> _rooms;
};

