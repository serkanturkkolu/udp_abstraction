#include <iostream>
#include "udp.h"
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

char recv_buf[1024];
int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Udp client(Udp::UdpClient);
    client.socket();
    client.write((unsigned char *)"Hello from Client!",strlen("Hello from Client!"));
    while(true){
        client.read((unsigned char*)recv_buf);
        cout << recv_buf << endl;
    }
    return 0;
}
