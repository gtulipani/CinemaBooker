#ifndef __COMMONS_SOCKET_H__
#define __COMMONS_SOCKET_H__

#include <string>

#include "commons_socket_t.h"

class Socket {
private:
	bool initialized;
	socket_t skt;

	socket_t* getSkt();
public:
	Socket();

	void connect(std::string host, std::string port);

	void bind(std::string port);

	Socket accept();

	void send(std::string source, unsigned long size);

	void send_int(int num);

	long receive(std::string& out, unsigned long size);

	int receive_int();

	~Socket();
};


#endif //__COMMONS_SOCKET_H__
