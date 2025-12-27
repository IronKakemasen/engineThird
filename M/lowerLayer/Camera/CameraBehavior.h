#pragma once
#include "../../utilities/Transform/Transform.h"


struct CameraBehavior
{
	Matrix4 vpMat;

	virtual void Update() = 0;

protected:
	void SetViewProjectionMat();
	Transform trans;

public:
	inline auto* Getter_Trans()
	{
		return &trans;
	}
};

struct Camera:CameraBehavior
{

};

