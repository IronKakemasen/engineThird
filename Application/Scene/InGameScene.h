#pragma once
#include "../../M/lowerLayer/Scene/SceneBehavior/SceneBehavior.h"
#include "../GameObject/Player.h"
#include "../GameObject/BlackBlock.h"
#include "../GameObject/BlockManager.h"
#include "../GameObject/GreenBlock.h"
#include "../GameObject/InGameController.h"
#include "../GameObject/NormalBlock.h"


class InGameScene final : public SceneBehavior
{
public:
	InGameScene();

	std::unique_ptr<Player> player;
	std::unique_ptr<BlackBlock> blackBlock;
	std::unique_ptr<GreenBlock> greenBlock;
	std::unique_ptr<NormalBlock> normalBlock;
	std::unique_ptr<BlockManager> blockManager;
	std::unique_ptr<InGameController> inGameController;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

private:

	virtual void Instantiate() override;
	virtual void Init() override;

};

