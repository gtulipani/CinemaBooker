#include <iostream>
#include "clientClient.h"
#include "commonsocket.h"
#include "clientConnectionRefusedException.h"

Client::Client(std::string server_ip, std::string port) :
	server_ip(std::move(server_ip)), port(std::move(port)) {}

void Client::start() {
	//socket_t socket;

	// Connect through the socket
	/*if (socket_connect(&socket, server_ip.c_str(), port.c_str()) ==
		SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}*/

	// Read command to be executed from cin
	//std::string input;
	//std::getline(std::cin, input);

	/*if (socket_send(&socket, input.c_str(), input.size()) == SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}*/

	// Closes the socket entirely
	//socket_close(&socket);
}
