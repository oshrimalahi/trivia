#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include "Helper.h"

// using static const instead of macros 
static const unsigned short PORT = 8820;
static const unsigned int IFACE = 0;

using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;


Communicator::Communicator()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		handleNewClient();
	}
}

// listen to connecting requests from clients
// accept them, and create thread for each client
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void Communicator::handleNewClient()
{
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	LoginRequestHandler* handler = new LoginRequestHandler();
	_clients[client_socket] = handler;
	std::thread tr(&Communicator::clientHandler, this, client_socket);
	tr.detach();
}

void Communicator::clientHandler(const SOCKET client_socket)
{
	RecvMessage* currRcvMsg = nullptr;
	try
	{	
		std::string msg = "Hello";
		Helper::sendData(client_socket, msg);
		std::string recv = Helper::getPartFromSocket(client_socket, 5, 0);
		std::cout << recv << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catch in function clientHandler. socket=" << client_socket << ", what=" << e.what() << std::endl;
	}
	closesocket(client_socket);
}
