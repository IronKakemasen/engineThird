#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/BlackModel.h"

struct BlackBlock : GameObject
{

public:
	std::unique_ptr<BlackModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	BlackBlock();

};

