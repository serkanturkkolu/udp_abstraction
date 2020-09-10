
#include "pch.h"
#include <iostream>
#include "UdpWin.h"

int main()
{
    std::cout << "Hello World!\n"; 
	UdpWin server(Udp::UdpServer);
	server.socket(8888);
	server.bind();
	char str[1024] = { 0 };
	server.read((unsigned char*)str);
	std::cout << "Gelen: " << str;
	server.write((unsigned char*)"Server is begin.", strlen("Server is begin."));
	while (true) {
		server.read((unsigned char*)str);
		std::cout << "Gelen: " << str;
	}

}

