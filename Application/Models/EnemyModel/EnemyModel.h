#pragma once
#include "ModelBehavior.h"


class EnemyModel :public ModelBehavior
{
	std::unique_ptr<ModelSimple> body;
	std::unique_ptr<ModelSimple> thorn;


public:
	std::vector<ModelSimple*> models;

	EnemyModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

