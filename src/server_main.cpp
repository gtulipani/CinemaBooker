#include <iostream>
#include <sstream>
#include <iomanip>

#include "server.h"
#include "server_InputFileException.h"
#include "server_ClientOperationException.h"
#include "server_InvalidInputParamsException.h"

#define SERVER_USAGE_PARAMETERS_HELP "Uso: ./server <puerto> <salas.csv> <peliculas.csv> <funciones.csv>"

#define SERVER_PROGRAM_RESULT_SUCCESS 0
#define SERVER_INPUT_PARAMS_ERROR 1
#define SERVER_INPUT_FILES_ERROR 2
#define SERVER_UNEXPECTED_ERROR 3

int main(int argc, char *argv[]) {
	if (argc != 5) {
		std::cout << SERVER_USAGE_PARAMETERS_HELP << std::endl;
		return SERVER_INPUT_PARAMS_ERROR;
	} else {
		try {
			// Server receives port, roomsCsv, moviesCsv, showingsCsv
			Server server(argv[1], argv[2], argv[3], argv[4]);
			server.start();
		} catch (InputFileException &e) {
			std::cerr << e.what() << std::endl;
			return SERVER_INPUT_PARAMS_ERROR;
		} catch (InvalidInputParamsException &e) {
			std::cerr << e.what() << std::endl;
			return SERVER_INPUT_FILES_ERROR;
		} catch (ClientOperationException &e) {
			std::cerr << e.what() << std::endl;
			return SERVER_INPUT_FILES_ERROR;
		} catch (std::runtime_error &e) {
			std::cerr << e.what() << std::endl;
			return SERVER_UNEXPECTED_ERROR;
		} catch (...) {
			std::cerr << "Unexpected error" << std::endl;
			return SERVER_UNEXPECTED_ERROR;
		}
	}
	return SERVER_PROGRAM_RESULT_SUCCESS;
}