#pragma once
#include "../ModelBehavior.h"

class SampleModel:public ModelBehavior
{


public:
	SampleModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;

};

