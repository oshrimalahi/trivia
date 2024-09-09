#pragma once

#include "Communicator.h"
#include <thread>
#include <atomic>


class Server : Communicator
{
public:
	Server();
	~Server();
	void run();

private:
	Communicator _communicator;
};
