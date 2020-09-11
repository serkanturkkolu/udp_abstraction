
#include <cstring>
#include <string>
#include "udp.h"
#include <stdlib.h>
#include <stdio.h>



#ifdef _WIN32

    #undef UNICODE

    #define WIN32_LEAN_AND_MEAN

    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
#ifdef _MSC_VER
    // Need to link with Ws2_32.lib
	#pragma comment (lib, "Ws2_32.lib")
    // #pragma comment (lib, "Mswsock.lib")
#endif
	
#elif defined __linux__ || defined __APPLE__

    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

#endif


int Udp::write(const unsigned char sending_data[],size_t len){
    if(type == UdpServer){
        return sendto(m_sockfd, (const char *)sending_data, len,  0, (const struct sockaddr *) &m_cli_addr, m_clilen); // MSG_CONFIRM for 0
    }
    else{
        return sendto(m_sockfd, (const char *)sending_data, len,  0, (const struct sockaddr *) &m_serv_addr, sizeof(m_serv_addr)); // MSG_CONFIRM for 0
    }

}

int Udp::read(unsigned char *read_data){
    if(type == UdpServer){
        return recvfrom(m_sockfd, (char *)read_data, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &m_cli_addr, &m_clilen); //MSG_WAITALL for 0;
    }
    else{
        return recvfrom(m_sockfd, (char *)read_data, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &m_serv_addr, &m_clilen); //MSG_WAITALL for 0;
    }

}

int Udp::socket(int port){
 
    sock_port_no =port;
    return socket();
}

int Udp::socket(){

#ifdef _WIN32
    WORD version = MAKEWORD(2, 2);
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != NO_ERROR) {
        printf("WSAStartup failed with error %d\n", res);
        return 1;
    }
#endif

    if ( (m_sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        return -1;
    }


    memset(&m_serv_addr, 0, sizeof(m_serv_addr));
    memset(&m_cli_addr, 0, sizeof(m_cli_addr));

 
    m_serv_addr.sin_family = AF_INET;
    m_serv_addr.sin_port = htons(sock_port_no);
	if (type == Udp::UdpServer) {
		m_serv_addr.sin_addr.s_addr = INADDR_ANY;
	}
	else {
#ifdef __MINGW32__
		m_serv_addr.sin_addr.s_addr = INADDR_ANY;
#else
		inet_pton(AF_INET, serverAddress, &m_serv_addr.sin_addr);
#endif
	}
    return 0;
}

int Udp::bind(){
    // Bind the socket with the server address
    if ( ::bind(m_sockfd, (const struct sockaddr *)&m_serv_addr, sizeof(m_serv_addr)) < 0 )
    {
        perror("bind failed");
        return -1;
    }


    m_clilen = sizeof(m_cli_addr);  //len is value/resuslt
    return 0;
}


int Udp::close() {
#ifdef _WIN32
    return closesocket(m_sockfd);
#elif defined __linux__ || defined __APPLE__
    return ::close(m_sockfd);
#endif

}

