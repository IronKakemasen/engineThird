#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"

struct InGameController : GameObject
{

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	InGameController();

};

