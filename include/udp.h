
#ifndef TCPIPSERVER__
#define TCPIPSERVER__ 

#if defined __linux__ || defined __APPLE__

#include <netinet/in.h>
#elif _WIN32
#pragma once
#include "winsock2.h"
#endif

#include <vector> 
#include <string> 
#include "iudp.h"

class Udp:public IUdp{
#ifdef _WIN32
#define MAX_BUFFER_SIZE 1024
private:
WSADATA wsaData;
struct sockaddr_in m_serv_addr;
int m_clilen = sizeof(m_serv_addr);

struct sockaddr_in m_cli_addr;
int clientAddrSize = sizeof(m_cli_addr);

SOCKET m_sockfd = INVALID_SOCKET;


#elif defined __linux__ || defined __APPLE__
private:
    int m_sockfd=-1;
    socklen_t m_clilen;
    static const int MAX_BUFFER_SIZE=1024;
    struct sockaddr_in m_serv_addr, m_cli_addr;
#endif
public:
    Udp(IUdp::Type t, const char *address = DEFAULT_ADDRESS, int port=DEFAULT_PORT,bool blocking=false):IUdp(t,address,port,blocking){}
    virtual int write(const unsigned char sending_data[],size_t len);
    virtual int read(unsigned char *);
    virtual void set_blocking_read(bool);
    virtual int set_blocking_time_ms(uint32_t);
    virtual int socket(int);
    virtual int socket();
    virtual int bind();
    virtual int close();
private: 

};

#endif

