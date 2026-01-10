#pragma once
#include "ModelBehavior.h"


class ShikouteiModel :public ModelBehavior
{

public:
	ShikouteiModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init()override;
	virtual void Reset()override;

};

