#pragma once
#include "ModelBehavior.h"

class EnemyFactoryModel :public ModelBehavior
{
	float const kMaxAmplitude = 0.35f;
	float shakeDeltaTheta = 0.0f;
	float kShakeSpeed = 12.0f;
	Counter zenmaiCnt;
	Counter zenmaiRotateCnt;
	float curRotateDegree = 0.0f;

	std::unique_ptr<ModelSimple> body;
	std::unique_ptr<ModelSimple> zenmai;

public:
	std::vector<ModelSimple*> models;

	EnemyFactoryModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};
