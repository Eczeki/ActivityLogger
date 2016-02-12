#include "DataStreamer.h"


DataStreamer::DataStreamer()
{
	/*std::ifstream in;
	in.open("server.txt");

	if (in.is_open())
	{
		std::getline(in, addr);		
	}*/
	addr = "eltsgaming.net";
}

void DataStreamer::startUp()
{
	/* Startup WSA */
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);	
	if (iResult != 0) {
		std::cout << "WSAStartup failed: " + iResult << std::endl;
		throw StartUpException();
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	/* Get the data of the address */
	iResult = getaddrinfo(addr.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {
		WSACleanup();
		throw GetAddrException();
	}

	ptr = result;

	/* Create socket */
	sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (sock == INVALID_SOCKET) {
		freeaddrinfo(result);
		WSACleanup();
		throw SocketException();
	}
}

void DataStreamer::connectToServer()
{
	/* Connect to server */
	iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);

	if (iResult == SOCKET_ERROR) {
		closesocket(sock);
		sock = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (sock == INVALID_SOCKET) {		
		WSACleanup();
		throw ServerConnectionException();
	}

}

bool DataStreamer::sendData(std::string data)
{
	iResult = send(sock, data.c_str(), (int)strlen(data.c_str()), 0);

	if (iResult == SOCKET_ERROR) {		
		closesocket(sock);
		WSACleanup();
		return false;
	}	
	return true;
}

std::string DataStreamer::getResponse()
{
	char recvbuf[1024];
	memset(recvbuf, 0, 1024);
	iResult = recv(sock, recvbuf, 1024, 0);
	return std::string(recvbuf);
}

DataStreamer::~DataStreamer()
{
	closesocket(sock);
	WSACleanup();
}
