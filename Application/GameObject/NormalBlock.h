#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/NormalModel.h"

struct NormalBlock : public GameObject
{

public:

	std::unique_ptr<NormalModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	NormalBlock();

};

