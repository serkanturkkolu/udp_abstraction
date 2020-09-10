
#ifndef _INTERFACECOMM_
#define _CRT_SECURE_NO_WARNINGS
#define _INTERFACECOMM_
#include <string.h>

class Udp {
#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 8888
public:
	enum Type {
		UdpServer,
		UdpClient
	};
protected:
	enum Type type;
public:
	Udp(Type t, const char *address = DEFAULT_ADDRESS, int port=DEFAULT_PORT) {
		type = t;

		memcpy(serverAddress, address,strlen(address)+1);
		sock_port_no = port;
	}
	virtual int write(const unsigned char sending_data[], size_t len) = 0;
	virtual int read(unsigned char *) = 0;
	virtual int socket(int) = 0;
	virtual int socket() = 0;
	virtual int bind() = 0;
	virtual int close() = 0;
protected:
	int sock_port_no;
	char serverAddress[32] = { 0 };
};


#endif
