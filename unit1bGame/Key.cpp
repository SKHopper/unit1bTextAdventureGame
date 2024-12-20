#include "Key.h"

constants::DOOR_TYPE Key::getKeyType(){
	int keyType = getInstanceData().at(0);
	return static_cast<constants::DOOR_TYPE>(keyType);
}