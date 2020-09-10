

#include <iostream>
#include "UdpWin.h"
#include <Windows.h>

int main()
{
	Sleep(3000);
	std::cout << "Hello World!\n";
	UdpWin client(Udp::UdpClient);
	client.socket(8888);
	char str[1024] = { 0 }; 

	client.write((unsigned char*)"Client is begin.",strlen("Client is begin."));
	client.read((unsigned char*)str);
	std::cout << "Gelen: " << str << std::endl;
	
	while (true) {

		int val = client.write((unsigned char*)"Client keep going.", strlen("Client keep going."));
		Sleep(1000);
		std::cout << "Data gonderildi. Deger: " << val << "\n";
	}


}
