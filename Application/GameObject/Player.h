#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/PlayerModel.h"

struct Player : public GameObject
{
	void ClipPosition();
	void Move();
	void SetStart();
	float const moveSpeed = 2.75f;
	Counter angleCnt;
	float nextAngleY = 0.0f;
	float preAngleY = 0.0f;
	float const playerSize = 0.2f;
public:
	std::unique_ptr<PlayerModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	Player();
};

