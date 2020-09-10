#include "pch.h"
#include "UdpWin.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


int UdpWin::socket(int port) { 

	sock_port_no = port;
	return socket();

}

int UdpWin::socket() { 

	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		printf("WSAStartup failed with error %d\n", res);
		return 1;
	}

	serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0); //IPPROTO_UDP
	if (serverSocket == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		return 1;
	}
	memset((char *)&serverAddr, 0, sizeof(serverAddr));
	// Bind the socket to any address and the specified port.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(sock_port_no);
	if (type == Udp::UdpServer) { 
		serverAddr.sin_addr.s_addr = INADDR_ANY;
	}
	else {
		inet_pton(AF_INET, serverAddress, &serverAddr.sin_addr);
	}
	// OR, you can do serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	return 0;

}

int UdpWin::bind() {

	if (::bind(serverSocket, (SOCKADDR *)& serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		return 1;
	}
	return 0;
}


int UdpWin::write(const unsigned char sending_data[], size_t len) {
	if (type == UdpServer) {
		return sendto(serverSocket, (char*)sending_data, len, 0, (SOCKADDR *)& clientAddr, clientAddrSize);
	}
	else {
		return sendto(serverSocket,	(char*)sending_data, len, 0, (SOCKADDR *)& serverAddr, sizeof(serverAddr));

	}
}

int UdpWin::read(unsigned char *recvbuf) {
	if (type == UdpServer) {
		int bytes_received = recvfrom(serverSocket, (char*)recvbuf, UDP_MAX_LENGTH, 0 /* no flags*/, (sockaddr *)& clientAddr, &clientAddrSize);

		if (bytes_received == SOCKET_ERROR) {
			printf("recvfrom failed with error %d\n", WSAGetLastError());
		}
		return bytes_received;
	}
	else {
		int bytes_received = recvfrom(serverSocket, (char*)recvbuf, UDP_MAX_LENGTH, 0 /* no flags*/, (sockaddr *)& serverAddr, &serverAddrSize);
		if (bytes_received == SOCKET_ERROR) {
			printf("recvfrom failed with error %d\n", WSAGetLastError());
		}
		char cliIp[256];
		ZeroMemory(cliIp, 256);
		inet_ntop(AF_INET, &clientAddr.sin_addr, cliIp, 256);
		printf("Messagce recvfrom from %s : %s \n", cliIp, recvbuf);

		return bytes_received;
	}
	  
}

int UdpWin::close() {
	return closesocket(serverSocket);
}

