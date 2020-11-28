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
    Udp server(Udp::Receiver,"127.0.0.1",8888,true);
    server.socket();
    server.bind(); 
    int counter=0;
    while(true){
        memset(recv_buf,0,sizeof recv_buf);
        if(counter++ == 10){ 
            server.set_blocking_time_ms(3900); 
        }else if(counter == 20){
            server.set_blocking_time_ms(1010); 
        }
        server.read((unsigned char*)recv_buf); 
        cout << "Receive data: " << recv_buf << endl;  
    }

    return 0;
}

