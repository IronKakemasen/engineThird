#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/BlackModel.h"
#include "BlockBehavior.h"

struct BlackBlock : public GameObject
{

public:

	std::unique_ptr<BlackModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	BlackBlock();

};

