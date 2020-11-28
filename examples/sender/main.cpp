#include <iostream>
#include "udp.h"
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

char recv_buf[1024];
int main()
{
    Udp client(Udp::Sender,"127.0.0.1",8888);
    client.socket();
    while(true){
        client.write((unsigned char *)"Hello from Client!",strlen("Hello from Client!"));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
