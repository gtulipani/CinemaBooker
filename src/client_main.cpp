#include <iostream>
#include "client.h"

#define CLIENT_PROGRAM_RESULT_SUCCESS 0
#define CLIENT_INPUT_PARAMS_ERROR 1

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: ./client <ip-servidor> <puerto-servidor>"
				  << std::endl;
		return CLIENT_INPUT_PARAMS_ERROR;
	} else {
		// Client receives ip, port
		Client client(argv[1], argv[2]);
		client.start();
	}
	return CLIENT_PROGRAM_RESULT_SUCCESS;
}

