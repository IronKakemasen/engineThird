#include "BlockManager.h"
#include "BlackBlock.h"
#include "NormalBlock.h"
#include "GreenBlock.h"
#include "InGameController.h"


void BlockManager::Update()
{

}

void BlockManager::Init()
{
	curLastPosZ = kStartPos.z;
	TurnBlocksIsActiveOff();
	SetGround();
}

void BlockManager::Reset()
{
	curLastPosZ = kStartPos.z;

}

void BlockManager::Draw(Matrix4* vpMat_)
{

}

void BlockManager::SetGround()
{
	int n = 0;
	for (float z = 0; z < waveData[InGameController::cur_wave].startSize.y; ++z)
	{
		for (float x = 0; x < waveData[InGameController::cur_wave].startSize.x; ++x)
		{
			for (float y = 0; y < float(height); ++y)
			{
				normalBlocks[n]->SetStatus(Status::kActive);
				normalBlocks[n++]->Getter_Trans()->pos = kStartPos +
				Vector3{x, -y, z};
			}
		}
	}
}

void BlockManager::TurnBlocksIsActiveOff()
{
	for (auto& block : normalBlocks)
	{
		block->SetStatus(Status::kInActive);
	}

	for (auto& block : blackBlocks)
	{
		block->SetStatus(Status::kInActive);
	}

	for (auto& block : greenBlocks)
	{
		block->SetStatus(Status::kInActive);
	}

}

void BlockManager::WaveData::Init(Vector2 startSize_, Vector4 color_)
{
	startSize = startSize_;
	color = color_;
}

BlockManager::BlockManager()
{
	waveData[0].Init({ 4,15 }, { 128,128,128,255 });
}

void BlockManager::SetNormalBlock(NormalBlock* nomal_)
{
	normalBlocks.emplace_back(nomal_);
}
void BlockManager::SetBlackBlock(BlackBlock* black_)
{
	blackBlocks.emplace_back(black_);
}

void BlockManager::SetGreenBlock(GreenBlock* green_)
{
	greenBlocks.emplace_back(green_);
}


