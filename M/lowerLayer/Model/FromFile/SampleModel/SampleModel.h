#pragma once
#include "../ModelBehavior.h"

class SampleModel:ModelBehavior
{


public:
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;

};

