#include <iostream>
#include <sstream>
#include <iomanip>

#include "server_ClientThread.h"
#include "server_ClientOperationException.h"
#include "commons_ClientClosedSocketException.h"

#define LIST_BY_LANGUAGE_OPERATION_IDENTIFIER "IDIOMA"
#define LIST_BY_AGE_OPERATION_IDENTIFIER "EDAD"
#define LIST_BY_GENRE_OPERATION_IDENTIFIER "GENERO"
#define LIST_BY_DATE_OPERATION_IDENTIFIER "FECHA"
#define LIST_SEATS_OPERATION_IDENTIFIER "ASIENTOS"
#define BOOK_SEAT_OPERATION_IDENTIFIER "RESERVA"

std::vector<std::string>
ClientThread::split(const std::string &s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream token_stream(s);
	while (std::getline(token_stream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void
ClientThread::processCommand(const std::string &input, Socket &client_socket) {
	std::vector<std::string> words = split(input, ' ');
	std::ostringstream stream;
	if (words[0] == LIST_BY_LANGUAGE_OPERATION_IDENTIFIER) {
		monitor.listMoviesByLanguage(words[1], stream);
	} else if (words[0] == LIST_BY_AGE_OPERATION_IDENTIFIER) {
		monitor.listMoviesByAge(words[1], stream);
	} else if (words[0] == LIST_BY_GENRE_OPERATION_IDENTIFIER) {
		monitor.listMoviesByGenre(words[1], stream);
	} else if (words[0] == LIST_BY_DATE_OPERATION_IDENTIFIER) {
		std::tm tm{};
		std::istringstream ss(words[1]);
		ss >> std::get_time(&tm, "%d/%m/%Y");
		monitor.listShowingsForDay(tm, stream);
	} else if (words[0] == LIST_SEATS_OPERATION_IDENTIFIER) {
		monitor.listSeatsFromShowingId(words[1], stream);
	} else if (words[0] == BOOK_SEAT_OPERATION_IDENTIFIER) {
		monitor.bookShowing(words[1], words[2], std::stoi(words[3]), stream);
	} else {
		throw ClientOperationException("Operation invalid: " + input);
	}
	std::string out = stream.str();
	unsigned long message_size = out.size();
	client_socket.send_int((int) message_size);
	client_socket.send(out, message_size);
}

ClientThread::ClientThread(Socket socket, CinemaMonitor &monitor) :
		Thread(),
		socket(std::move(socket)),
		monitor(monitor) {}

void ClientThread::run() {
	bool socket_closed = false;
	try {
		while (alive) {
			// Receive commands from the socket
			std::string input;
			std::string output;
			long bytes_received = 0;
			do {
				// Waiting for int with quantity of bytes. Will throw exception
				// if the client closes the socket
				int size_len = socket.receive_int();
				bytes_received = socket.receive(input,
												static_cast<unsigned long>(size_len));
				if (bytes_received > 0) {
					processCommand(input, socket);
				}
			} while (bytes_received > 0);
		}
	} catch (ClientClosedSocketException &e) {
		// Means that the client has finished all its operations and closed the
		// socket
		socket_closed = true;
		alive = false;
	}

	if (!socket_closed) {
		socket.close();
	}
}

ClientThread::~ClientThread() {
	socket.close();
}
