#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/PlaneModel.h"

struct BlueMark : public GameObject
{
	struct ToBlock
	{
		BlueMark* p;
		bool operator()();
		void Init(BlueMark* p_);
	};

	std::unique_ptr < PlaneModel > model;

public:
	enum Mode
	{
		kExist,
		kNotExist,
		kActivated

	};

	PointLight* p;
	Mode mode = kNotExist;
	ToBlock toBlock;
	Counter markingCnt;
	float const markTime = 0.25f;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	BlueMark();

};

