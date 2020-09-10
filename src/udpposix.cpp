
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include "udpposix.h"


int UdpLinux::write(const unsigned char sending_data[],size_t len){
    if(type == UdpServer){
        return sendto(m_sockfd, (const char *)sending_data, len,  0, (const struct sockaddr *) &m_cli_addr, m_clilen); // MSG_CONFIRM for 0
    }
    else{
        return sendto(m_sockfd, (const char *)sending_data, len,  0, (const struct sockaddr *) &m_serv_addr, sizeof(m_serv_addr)); // MSG_CONFIRM for 0
    }

}

int UdpLinux::read(unsigned char *read_data){
    if(type == UdpServer){
        return recvfrom(m_sockfd, (char *)read_data, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &m_cli_addr, &m_clilen); //MSG_WAITALL for 0;
    }
    else{
        return recvfrom(m_sockfd, (char *)read_data, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &m_serv_addr, &m_clilen); //MSG_WAITALL for 0;
    }

}

int UdpLinux::socket(int port){
 
    sock_port_no =port;
    return socket();
}

int UdpLinux::socket(){

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
		inet_pton(AF_INET, serverAddress, &m_serv_addr.sin_addr);
	}
    return 0;
}

int UdpLinux::bind(){
    // Bind the socket with the server address
    if ( ::bind(m_sockfd, (const struct sockaddr *)&m_serv_addr, sizeof(m_serv_addr)) < 0 )
    {
        perror("bind failed");
        return -1;
    }


    m_clilen = sizeof(m_cli_addr);  //len is value/resuslt
    return 0;
}


int UdpLinux::close() {
	return ::close(m_sockfd);
}

