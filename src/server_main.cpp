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

			/*std::cout << "Listing movies by language: ESP" << std::endl;
			server.listMoviesByLanguage("ESP");

			std::cout << "Listing movies by age: ATP" << std::endl;
			server.listMoviesByAge("ATP");

			std::cout << "Listing movies by genre: Terror" << std::endl;
			server.listMoviesByGenre("Terror");

			std::cout << "Listing showings for day: 13/10/2018" << std::endl;
			std::tm tm = {};
			std::stringstream ss("13/10/2018");
			ss >> std::get_time(&tm, "%d/%m/%Y");
			server.listShowingsForDay(tm);

			std::cout << "Listing seats from showing id: 2" << std::endl;
			server.listSeatsFromShowingId("2");

			std::cout << "Booking seat with row A and column 1 in showing id 2"
					  << std::endl;
			server.bookShowing("2", 'A', 1);

			std::cout << "Reprinting seats for that same showing" << std::endl;
			server.listSeatsFromShowingId("2");*/
		} catch (InputFileException &e) {
			return SERVER_INPUT_PARAMS_ERROR;
		} catch (InvalidInputParamsException &e) {
			return SERVER_INPUT_FILES_ERROR;
		} catch (ClientOperationException &e) {
			return SERVER_INPUT_FILES_ERROR;
		} catch (std::runtime_error &e) {
			return SERVER_UNEXPECTED_ERROR;
		} catch (...) {
			return SERVER_UNEXPECTED_ERROR;
		}
	}
	return SERVER_PROGRAM_RESULT_SUCCESS;
}