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
	std::vector<std::unique_ptr<BlackBlock>> blackBlocks;
	std::vector<std::unique_ptr<GreenBlock>> greenBlocks;
	std::vector<std::unique_ptr<NormalBlock>> normalBlocks;
	std::unique_ptr<BlockManager> blockManager;
	std::unique_ptr<InGameController> inGameController;
	PointLight* pointLights[3];

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

private:

	virtual void Instantiate() override;
	virtual void Init() override;

};

