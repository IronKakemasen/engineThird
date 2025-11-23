#pragma once
#include "../Transform/Transform.h"

struct CameraBehavior
{
	Transform trans;
	Matrix4 vpMat;

	virtual void Update() = 0;

protected:
	void SetViewProjectionMat();

};

