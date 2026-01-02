#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/GreenModel.h"

struct GreenBlock : public GameObject
{

public:
	std::unique_ptr<GreenModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	GreenBlock();

};

