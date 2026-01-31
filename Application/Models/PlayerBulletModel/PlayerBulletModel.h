#pragma once
#include "ModelBehavior.h"


class PlayerBulletModel :public ModelBehavior
{

public:
	Vector3 randomRotateAddNum;
	float rotateSpeed = 12.0f;

	PlayerBulletModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

