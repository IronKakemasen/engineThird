#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"

struct BlockManager : GameObject
{

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	BlockManager();

};

