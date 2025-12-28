#pragma once
#include "../ModelBehavior.h"

class SampleModel2 :public ModelBehavior
{
public:
	SampleModel2();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init()override;
	virtual void Reset()override;

};

