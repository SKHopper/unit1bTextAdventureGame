#include "Key.h"

constants::DOOR_TYPE Key::getKeyType(){
	return static_cast<constants::DOOR_TYPE>(getInstanceData().at(0));
}
