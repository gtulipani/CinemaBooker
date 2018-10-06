#ifndef __SERVER_CLIENT_THREAD_H__
#define __SERVER_CLIENT_THREAD_H__

#include "commons_Socket.h"
#include "server_Thread.h"
#include "server_CinemaMonitor.h"

class ClientThread : public Thread {
private:
	Socket socket;
	CinemaMonitor &monitor;

	std::vector<std::string> split(const std::string &s, char delimiter);

	void processCommand(const std::string &input, Socket &client_socket);
public:
	explicit ClientThread(Socket socket, CinemaMonitor &monitor);

	void run() override;

	~ClientThread() override;
};


#endif //__SERVER_CLIENT_THREAD_H__
