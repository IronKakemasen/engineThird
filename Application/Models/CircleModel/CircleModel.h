#pragma once
#include "ModelBehavior.h"

class CircleModel :public ModelBehavior
{
	float deltaTheta = 0.0f;

public:
	Vector3 defaultScale = { 1,1,1 };

	CircleModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

