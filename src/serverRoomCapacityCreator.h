#ifndef __ROOM_CAPACITY_CREATOR_H__
#define __ROOM_CAPACITY_CREATOR_H__

#include <string>

#include "serverSmallRoomCapacity.h"
#include "serverMediumRoomCapacity.h"
#include "serverLargeRoomCapacity.h"


/**
 * Class that handles the logic to create the proper capacity based on the identifier
 */
class RoomCapacityCreator {
private:
	static SmallRoomCapacity *
	createSmallRoomCapacity(std::string capacity);

	static MediumRoomCapacity *
	createMediumRoomCapacity(std::string capacity);

	static LargeRoomCapacity *
	createLargeRoomCapacity(std::string capacity);
public:
	static RoomCapacity *factoryMethod(std::string capacity);

};


#endif //__ROOM_CAPACITY_CREATOR_H__
