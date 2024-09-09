#include "Server.h"
#include <iostream>
#include <string>

Server::Server() {}

Server::~Server() {}

void Server::run()
{
    std::thread t_connector([this]() {_communicator.startHandleRequests(); });
    t_connector.detach();

    std::string command;
    while (true)
    {
        std::getline(std::cin, command);
        if (command == "EXIT")
        {
            std::cout << "Closed server..." << std::endl;
            _communicator.~Communicator();
            break;
        }
    }
}
