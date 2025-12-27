#pragma once
#include "../bufferAndMap.h"
#include "../../../../math/vector/vector.h"


struct CameraPara
{
	Vector3 cameraWorld;
};

struct CameraParaBuffer
{
	BufferAndMap<CameraPara> cameraPara;
};


