#include <iostream>
#include <string>

#include "commons_Socket.h"
#include "commons_ConnectionRefusedException.h"

Socket::Socket() : initialized(false) {}

void Socket::connect(std::string host, std::string port) {
	// Connect through the socket
	if (socket_connect(&skt, host.c_str(), port.c_str()) ==
			SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
	initialized = true;
}

void Socket::send(std::string source, unsigned long size) {
	if (!initialized) {
		throw ConnectionRefusedException();
	}
	// Send message through the socket
	if (socket_send(&skt, source.c_str(), size) == SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
}

long Socket::receive(std::string& out, unsigned long size) {
	if (!initialized) {
		throw ConnectionRefusedException();
	}
	char* buffer = (char*) malloc(size);
	long bytes_received = socket_recv(&skt, buffer, size);
	if (bytes_received == SOCKET_CONNECTION_ERROR) {
		free(buffer);
		throw ConnectionRefusedException();
	}
	out = std::string(buffer, static_cast<unsigned long>(bytes_received));
	free(buffer);
	return bytes_received;
}

Socket::~Socket() {
	if (!initialized) {
		socket_close(&skt);
	}
}
