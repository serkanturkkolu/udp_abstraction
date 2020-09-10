#include <iostream>
#include "udp.h"
#include <cstring>

using namespace std;

char recv_buf[1024];
int main()
{
    Udp client(Udp::UdpClient);
    client.socket();
    client.write((unsigned char *)"Hello from Client!",strlen("Hello from Client!"));
    while(true){
        client.read((unsigned char*)recv_buf);
        cout << recv_buf << endl;
    }
    return 0;
}
