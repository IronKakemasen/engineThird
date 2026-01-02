#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/PlayerModel.h"

struct Player : public GameObject
{

public:
	std::unique_ptr<PlayerModel> model;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	Player();
};

