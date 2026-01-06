#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/NormalModel.h"
#include "BlockBehavior.h"

struct NormalBlock : public GameObject
{

public:
	Vector3 addStartPos;
	bool forAddition = false;
	bool rakka = false;
	std::unique_ptr<NormalModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	NormalBlock();

};

