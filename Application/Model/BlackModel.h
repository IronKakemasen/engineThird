#pragma once
#include "../../M/lowerLayer/Model/FromFile/ModelBehavior.h"

struct BlackModel :public ModelBehavior
{

public:
	BlackModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init()override;
	virtual void Reset()override;

};

