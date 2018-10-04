#ifndef __COMMONS_SOCKET_H__
#define __COMMONS_SOCKET_H__

#include <string>

#include "commons_socket_t.h"

class Socket {
private:
	bool initialized;
	socket_t skt;
public:
	Socket();

	void connect(std::string host, std::string port);

	void send(std::string source, unsigned long size);

	long receive(std::string& out, unsigned long size);

	~Socket();
};


#endif //__COMMONS_SOCKET_H__
