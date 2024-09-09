#pragma once

#include <string>
#include <vector>
#include <Windows.h>


class RecvMessage
{
public:
	RecvMessage(const SOCKET sock, const int messageCode) : _sock(sock), _messageCode(messageCode) {}
	inline RecvMessage(const SOCKET sock, const int messageCode, const std::vector<std::string> values) { _values = values; }
	inline SOCKET getSock() { return _sock; }
	inline int getMessageCode() { return _messageCode; }
	inline std::vector<std::string>& getValues() { return _values; }

private:
	SOCKET _sock;
	int _messageCode;
	std::vector<std::string> _values;
};
