#pragma once
#include <dinput.h>

class KeyboardKeys
{
	BYTE keys[256] = {};
	BYTE preKeys[256] = {};

public:

	inline BYTE* Getter_Key()
	{
		return keys;
	}

	bool IsKeyTrigger(int key_);
	bool IsKeyPress(int key_);
	void Copy();


};

