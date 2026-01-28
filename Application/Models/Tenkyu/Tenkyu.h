#pragma once
#include "ModelBehavior.h"


class Tenkyu :public ModelBehavior
{

public:
	Tenkyu();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

