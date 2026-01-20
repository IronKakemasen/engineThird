#pragma once
#include "ModelBehavior.h"


class PlayerAllyModel :public ModelBehavior
{

public:
	PlayerAllyModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

