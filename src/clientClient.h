#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>

class Client {
private:
	std::string server_ip;
	std::string port;
public:
	Client(std::string server_ip, std::string port);

	void start();
};


#endif //__CLIENT_H__
