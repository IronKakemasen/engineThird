#pragma once
#include "../bufferAndMap.h"
#include "../../../../math/vector/vector.h"


struct CameraPara
{
	Vector3 cameraWorld;
	float pad;
};

struct CameraParaBuffer
{
	BufferAndMap<CameraPara> cameraPara;
};


