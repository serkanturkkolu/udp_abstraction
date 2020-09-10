#include <iostream>
#include  <cstddef>
#include "udp.h"
#include <chrono>
#include <thread>
#include <cstring>

using namespace std;


char recv_buf[1024];

int main()
{
    Udp server(Udp::UdpServer);
    server.socket();
    server.bind();
    int recv_size=server.read((unsigned char*)recv_buf);
    cout << "Receive data: " << recv_buf << endl;
    memset(recv_buf,0,recv_size);
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        server.write((unsigned char *)"Hello from Server!",strlen("Hello from Server!"));
    }

    return 0;
}

