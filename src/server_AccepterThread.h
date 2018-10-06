#ifndef __SERVER_ACCEPTER_THREAD_H__
#define __SERVER_ACCEPTER_THREAD_H__

#include <string>

#include "server_CinemaMonitor.h"
#include "server_Thread.h"
#include "commons_Socket.h"

class AccepterThread : public Thread {
private:
	Socket &socket;
	CinemaMonitor &monitor;

public:
	AccepterThread(Socket &socket, CinemaMonitor &monitor);

	void run() override;

	~AccepterThread() override = default;
};

#endif //__SERVER_ACCEPTER_THREAD_H__
