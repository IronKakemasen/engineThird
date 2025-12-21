#pragma once
#include "../../GameObjectBehavior.h"
#include "../../../Model/MobilePrimitive/MobileTriangle/MTriangle/MTriangle.h"

class SampleEnemy:GameObject
{
	MTriangle triangleModel;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	SampleEnemy();
};

