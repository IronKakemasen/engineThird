#pragma once
#include "ModelBehavior.h"


class EnemyTowerModel :public ModelBehavior
{
	float const kMaxAmplitude = 0.35f;
	float shakeDeltaTheta = 0.0f;
	float kShakeSpeed = 12.0f;

public:
	EnemyTowerModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

