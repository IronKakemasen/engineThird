#pragma once
#include "../../GameObjectBehavior.h"
#include "../../../Model/FromFile/SampleModel/SampleModel.h"

class SampleObj :public GameObject
{
	SampleModel sModel;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	SampleObj();
};

