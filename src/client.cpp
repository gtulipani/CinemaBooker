#include <iostream>

#include "client.h"
#include "commons_ConnectionRefusedException.h"
#include "commons_Socket.h"

#define CHUNK_SIZE 10

Client::Client(std::string server_ip, std::string port) :
		server_ip(std::move(server_ip)), port(std::move(port)) {}

void Client::start() {
	Socket socket{};
	socket.connect(server_ip, port);

	// Read command to be executed from cin
	std::string input;
	std::string output;
	while (std::cin.peek() != '\n') {
		std::getline(std::cin, input);
		unsigned long input_size = input.size();
		socket.send_int(static_cast<int>(input_size));
		socket.send(std::move(input), input_size);

		// The quantity of bytes to expect
		auto expected_bytes = static_cast<unsigned long>(socket.receive_int());
		while (expected_bytes > 0) {
			unsigned long chunk_size = (expected_bytes < CHUNK_SIZE)
									   ? expected_bytes : CHUNK_SIZE;
			expected_bytes -= socket.receive(output, chunk_size);
			std::cout << output;
		}
	}
}
