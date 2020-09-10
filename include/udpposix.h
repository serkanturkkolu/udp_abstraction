
#if defined __linux__ || defined __APPLE__

#ifndef TCPIPSERVER__
#define TCPIPSERVER__ 
#include <netinet/in.h>
#include <vector> 
#include <string> 
#include "udp.h"

class UdpLinux:public Udp{
public:
    UdpLinux(Udp::Type t):Udp(t){}
    virtual int write(const unsigned char sending_data[],size_t len);
    virtual int read(unsigned char *);
    virtual int socket(int);
    virtual int socket();
    virtual int bind();
    virtual int close();
private: 
    int m_sockfd=-1;
    socklen_t m_clilen;
    static const int MAX_BUFFER_SIZE=1024;
    struct sockaddr_in m_serv_addr, m_cli_addr;

};

#endif

#endif
