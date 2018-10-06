#include <string>

#include "server_InputFileException.h"

InputFileException::InputFileException(std::string file_path)
		: runtime_error("El archivo " + file_path + " no existe.") {}
