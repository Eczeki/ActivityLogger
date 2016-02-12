#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <assert.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

class DataStreamer
{
public:
	DataStreamer(std::string addr);
	~DataStreamer();
	void startUp();
	void connectToServer();	
	bool sendData(std::string data);
	std::string getResponse();

private:
	struct addrinfo *result = NULL, *ptr = NULL, hints;	
	SOCKET sock = INVALID_SOCKET;
	std::string addr, port = "80";
	WSADATA wsaData;
	int iResult;

};

class StartUpException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Startup failed\n";
	}
};

class GetAddrException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "getaddrinfo failed\n";
	}
};

class SocketException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Error creating socket\n";
	}
};

class ServerConnectionException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot connect to server\n";
	}
};