#ifndef __CLIENT_CLOSED_SOCKET_EXCEPTION_H__
#define __CLIENT_CLOSED_SOCKET_EXCEPTION_H__

#include <stdexcept>

class ClientClosedSocketException : public std::runtime_error {
public:
	explicit ClientClosedSocketException();
};


#endif //__CLIENT_CLOSED_SOCKET_EXCEPTION_H__
