#include <iostream>
#include "udplinux.h"
#include <unistd.h>
#include <cstring>

using namespace std;
char recv_buf[1024];
int main()
{
    UdpLinux client(Udp::UdpClient);
    client.socket();
    client.write((unsigned char *)"Hello from Client!",strlen("Hello from Client!"));
    while(true){
        client.read((unsigned char*)recv_buf);
        cout << recv_buf << endl;
    }
    return 0;
}
