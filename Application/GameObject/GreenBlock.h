#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/GreenModel.h"
#include "BlockBehavior.h"

class PointLight;
struct RedMark;

struct GreenBlock : public GameObject
{

public:
	PointLight* light = nullptr;
	std::unique_ptr<GreenModel> model;
	RedMark* redMark = nullptr;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	GreenBlock();

};

