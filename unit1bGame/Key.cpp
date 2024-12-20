#include "Key.h"

constants::DOOR_TYPE Key::getKeyType(){
	return static_cast<constants::DOOR_TYPE>(static_cast<int>(getInstanceData().at(0)));
}