#pragma once
#include <string>

struct RoomData
{
    unsigned int idRoom;               
    std::string roomName;                
    unsigned int maxPlayers;             
    unsigned int numOfQuestionsInGame;   
    unsigned int timePerQuestion;        
    bool isActive;               
};