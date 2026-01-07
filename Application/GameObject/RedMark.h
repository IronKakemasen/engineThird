#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/KiiroModel.h"

class PointLight;

struct RedMark : public GameObject
{
	struct ToBlock
	{
		RedMark* p;
		bool operator()();
		void Init(RedMark* p_);
	};

	std::unique_ptr < KiiroModel > model;

public:

	enum Mode
	{
		kExist,
		kNotExist,
		kActivated
	};

	Mode mode = kNotExist;
	PointLight* p;
	ToBlock toBlock;
	Counter markingCnt;
	float const markTime = 0.25f;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;


	RedMark();

};

