#include <iostream>
#include  <cstddef>
#include "udpposix.h"
#include <chrono>
#include <cstring>

using namespace std;
using namespace std::chrono_literals;

char recv_buf[1024];

int main()
{
    UdpLinux server(Udp::UdpServer);
    server.socket();
    server.bind();
    int recv_size=server.read((unsigned char*)recv_buf);
    cout << "Receive data: " << recv_buf << endl;
    memset(recv_buf,0,recv_size);
    while(true){
        chrono::sleep_for(1s);
        server.write((unsigned char *)"Hello from Server!",strlen("Hello from Server!"));
    }

    return 0;
}

