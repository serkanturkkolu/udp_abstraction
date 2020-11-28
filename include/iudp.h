
#ifndef _INTERFACECOMM_
#define _CRT_SECURE_NO_WARNINGS
#define _INTERFACECOMM_
#include <string.h>

class IUdp {
#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 8888
public:
	enum Type {
		Receiver,
		Sender
	};
protected:
	enum Type m_type;
public:
    IUdp(Type t, const char *address = DEFAULT_ADDRESS, int port=DEFAULT_PORT,bool blocking=false) {
		m_type = t;

		memcpy(m_server_address, address,strlen(address)+1);
		m_sock_port_no = port;
		m_blocking=blocking;
	}
	virtual int write(const unsigned char sending_data[], size_t len) = 0;
	virtual int read(unsigned char *) = 0;
	virtual void set_blocking_read(bool) = 0;
	virtual int set_blocking_time_ms(uint32_t) = 0;
	virtual int socket(int) = 0;
	virtual int socket() = 0;
	virtual int bind() = 0;
	virtual int close() = 0;
protected:
	int m_sock_port_no;
	char m_server_address[32]="";
	bool m_blocking;
	uint32_t m_timeout_read_blocking=1010;
};
 

#endif
