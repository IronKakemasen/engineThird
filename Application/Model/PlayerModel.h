#pragma once
#include "../../M/lowerLayer/Model/FromFile/ModelBehavior.h"

struct PlayerModel :public ModelBehavior
{

public:
	PlayerModel(Transform* gameObject_);
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init()override;
	virtual void Reset()override;

};

