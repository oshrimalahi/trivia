#pragma once

#include <map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "RecvMessage.h"
#include "IRequestHandler.h"


class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient();
	void clientHandler(const SOCKET client_socket);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;
	std::queue<RecvMessage*> _messageHandler;
	std::mutex _mtxReceivedMessages;
	std::condition_variable _msgQueueCondition;
};
