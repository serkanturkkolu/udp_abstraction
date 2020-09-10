#pragma once
#include "udp.h"
#include "winsock2.h"

class UdpWin : public Udp
{
	#define UDP_MAX_LENGTH 1024
private:
	WSADATA wsaData;
	struct sockaddr_in serverAddr;
	int serverAddrSize = sizeof(serverAddr);

	struct sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);

	SOCKET serverSocket = INVALID_SOCKET;


public:
	UdpWin(Udp::Type t):Udp(t){}
	UdpWin(Udp::Type t, const char *address, int port) :Udp(t,address,port) {}
	virtual int write(const unsigned char sending_data[], size_t len);
	virtual int read(unsigned char *);
	virtual int socket(int);
	virtual int socket();
	virtual int bind();
	virtual int close();
};

