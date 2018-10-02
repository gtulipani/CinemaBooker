#include "commons_Socket.h"
#include "commons_ConnectionRefusedException.h"

Socket::Socket() : skt(nullptr) {}

void Socket::connect(std::string host, std::string port) {
	// Connect through the socket
	if (socket_connect(skt, host.c_str(), port.c_str()) ==
			SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
}

void Socket::send(std::string source, unsigned long size) {
	if (skt == nullptr) {
		throw ConnectionRefusedException();
	}
	// Send message through the socket
	if (socket_send(skt, source.c_str(), size) == SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
}

long Socket::receive(std::string out, unsigned long size) {
	if (skt == nullptr) {
		throw ConnectionRefusedException();
	}
	char* buffer = (char*) malloc(size);
	long bytes_received = socket_recv(skt, buffer, size);
	if (bytes_received == SOCKET_CONNECTION_ERROR) {
		free(buffer);
		throw ConnectionRefusedException();
	}
	out = std::string(buffer, static_cast<unsigned long>(bytes_received));
	free(buffer);
	return bytes_received;
}

Socket::~Socket() {
	if (skt != nullptr) {
		socket_close(skt);
	}
}
