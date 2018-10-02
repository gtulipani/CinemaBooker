#ifndef __SEAT_ALREADY_BOOKED_EXCEPTION_H__
#define __SEAT_ALREADY_BOOKED_EXCEPTION_H__

#include <stdexcept>
#include <string>

class SeatAlreadyBookedException : public std::runtime_error {
public:
	explicit SeatAlreadyBookedException(std::string message);
};


#endif //__SEAT_ALREADY_BOOKED_EXCEPTION_H__
