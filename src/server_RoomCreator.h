#ifndef __SERVER_ROOM_CREATOR_H__
#define __SERVER_ROOM_CREATOR_H__

#include <string>

#include "server_SmallRoom.h"
#include "server_MediumRoom.h"
#include "server_LargeRoom.h"

/**
 * Class that handles the logic to create the proper Room based on the identifier
 */
class RoomCreator {
private:
	static SmallRoom *
	createSmallRoom(std::string id_as_string, std::string room_type);

	static MediumRoom *
	createMediumRoom(std::string id_as_string, std::string room_type);

	static LargeRoom *
	createLargeRoom(std::string id_as_string, std::string room_type);

public:
	static Room *factoryMethod(std::string id_as_string, std::string room_type,
							   std::string capacity);
};

#endif //__SERVER_ROOM_CREATOR_H__
