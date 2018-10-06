#include <iostream>
#include <algorithm>

#include "server_AccepterThread.h"
#include "server_ClientThread.h"
#include "commons_ConnectionRefusedException.h"

AccepterThread::AccepterThread(Socket &socket, CinemaMonitor &monitor) :
		Thread(),
		socket(socket),
		monitor(monitor) {}

void AccepterThread::run() {
	std::vector<Thread *> threads;
	try {
		while (alive) {
			Socket client_socket = socket.accept();
			ClientThread *client = new ClientThread(std::move(client_socket),
													monitor);
			client->start();
			threads.emplace_back(client);
			std::for_each(threads.begin(), threads.end(), [&](Thread *client) {
				if (client->isDead()) {
					client->join();
					delete client;
				}
			});
		}
	} catch (ConnectionRefusedException &ignored) {
		// Accept will throw this exception when the server closes the socket
		// and stop waiting for new connections
	}

	std::for_each(threads.begin(), threads.end(), [&](Thread *client) {
		client->stop();
		client->join();
		delete client;
	});
}
