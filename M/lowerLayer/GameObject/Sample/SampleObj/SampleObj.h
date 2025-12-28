#pragma once
#include "../../GameObjectBehavior.h"
#include "../../../Model/FromFile/SampleModel/SampleModel.h"
#include "../../../Model/FromFile/SampleModel2/SampleModel2.h"


class SampleObj :public GameObject
{
	SampleModel sModel;
	SampleModel2 sModel2;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	SampleObj();
};

