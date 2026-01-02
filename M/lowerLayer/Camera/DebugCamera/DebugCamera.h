#pragma once
#include "../CameraBehavior.h"

struct DebugCamera :Camera
{
	virtual void Update()override;
	void ParallelMove();
	DebugCamera();
};

