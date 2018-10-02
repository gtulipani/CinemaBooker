#include <utility>
#include <list>

#include "serverRoomType.h"
#include "serverInvalidRoomException.h"

void RoomType::validateRoomType() {
	std::list<std::string> valid_type{"2D", "3D", "4D"};

	if ((std::find(valid_type.begin(), valid_type.end(), type)) ==
			valid_type.end()) {
		throw InvalidRoomException("Invalid Room Type");
	}
}

RoomType::RoomType(std::string type) : type(std::move(type)) {
	validateRoomType();
}

bool RoomType::operator==(const RoomType &other) const {
	return (type == other.type);
}

RoomType::RoomType(const RoomType &other) : RoomType(other.type) {}

RoomType::RoomType(RoomType&& other) noexcept : RoomType(std::move(other.type)) {}

RoomType& RoomType::operator=(const RoomType &other) {
	if (this == &other) {
		return *this; // other is myself!
	}
	this->type = other.type;

	return *this;
}

RoomType& RoomType::operator=(RoomType&& other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->type = std::move(other.type);

	return *this;
}
