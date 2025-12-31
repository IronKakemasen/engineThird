#include "KeyboardKeys.h"

bool KeyboardKeys::IsKeyTrigger(int key_)
{
	bool ret = false;

	if (keys[key_] && !preKeys[key_]) ret = true;

	return ret;
}

bool KeyboardKeys::IsKeyPress(int key_)
{
	bool ret = false;

	if (keys[key_]) ret = true;

	return ret;
}
void KeyboardKeys::Copy()
{
	memcpy(preKeys, keys, 256);
}

