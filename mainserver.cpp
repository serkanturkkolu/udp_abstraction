#include <iostream>
#include  <cstddef>
#include "udplinux.h"
#include <unistd.h>
#include <cstring>

using namespace std;
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
        sleep(1);
        server.write((unsigned char *)"Hello from Server!\n",strlen("Hello from Server!\n"));
    }

    return 0;
}

