#include "BlockManager.h"
#include "BlackBlock.h"
#include "NormalBlock.h"
#include "GreenBlock.h"
#include "InGameController.h"

void BlockManager::Update()
{
	switch (InGameController::mode)
	{
	case InGameController::kEnter:

		break;

	case InGameController::kPlayable:

		AddBlockToLast();
		break;

	case InGameController::kDeath:

		break;

	case InGameController::kClear:

		break;

	case InGameController::kResult:

		break;

	}

}

void BlockManager::Init()
{
	mapLast = 0;
	curLastPosZ = kStartPos.z;
	TurnBlocksIsActiveOff();
	SetAdditions();
	SetGround();

}

void BlockManager::Reset()
{
	curLastPosZ = kStartPos.z;
	mapLast = 0;

	for (auto itr = normalBlocks.begin(); itr != normalBlocks.end(); ++itr)
	{
		(*itr)->SetStatus(Status::kInActive);
	}
	SetGround();

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
				additions[n]->SetStatus(Status::kActive);
				additions[n++]->Getter_Trans()->pos = kStartPos +
				Vector3{x, -y, z};
			}
		}
	}
}

void BlockManager::AddBlockToLast()
{
	if (InGameController::numBreak > 0) return;

	float const offsetZ = - mapLast * kBlockSize;
	int n = 0;

	mapLast++;
	for (float z = 0; z < 1; ++z)
	{
		for (float x = 0; x < waveData[InGameController::cur_wave].startSize.x; ++x)
		{
			for (float y = 0; y < float(height); ++y)
			{
				while (1)
				{
					if (additions[n]->GetStatus() == Status::kInActive)
					{
						break;
					}
					n++;
				}

				additions[n]->SetStatus(Status::kActive);
				additions[n++]->Getter_Trans()->pos = kStartPos +
					Vector3{ x, -y, offsetZ };
			}
		}
	}
	InGameController::numBreak = 1;
}
void BlockManager::SetAdditions()
{
	int n = 0;
	for(auto itr = normalBlocks.begin(); itr != normalBlocks.end();++itr)
	{
		auto* it = additions.emplace_back((*itr));
		it->forAddition = true;
		n++;
		if (n >= numAdd)
		{
			break;
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
	waveData[0].Init({ 5,16 }, { 128,128,128,255 });
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


