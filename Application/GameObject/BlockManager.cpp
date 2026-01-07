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
		SetGround();

		GenerateBlocks();
		MakeBlockToEnter();
		break;

	case InGameController::kPlayable:
		GenerateBlocks();
		MakeBlockToEnter();
		if (geneCnt.count < 1.0f) return;

		MoveBlocks();

		if (CheckAllVanished())
		{
			if (CheckIsPerfect())
			{
				AddBlockToLast();
			}

			AddPerformance();
		}

		if (CheckVanish())
		{
			Vanish();
		}

		break;

	case InGameController::kDeath:

		break;

	case InGameController::kClear:

		break;

	case InGameController::kResult:

		break;

	}

}

bool BlockManager::CheckVanish()
{
	vanishNum = doVanishRow;
	doVanishRow = 0;

	if (M::GetInstance()->IsKeyTriggered(KeyType::O))
	{
		vanishNum++;
	}

	if (numFall >= 4)
	{
		int buff = numFall / 4;
		vanishNum += buff;
		numFall -= buff * 4;
	}

	if (vanishNum > 0)
	{
		return true;
	}

	return false;
}

void BlockManager::Vanish()
{
	float const offsetMaxZ = kStartPos.z + (mapLast + vanishNum - 1) * kBlockSize;
	float const offsetMinZ = kStartPos.z + (mapLast) * kBlockSize;

	float min = offsetMinZ - 0.2f;
	float max = offsetMaxZ + 0.2f;

	for (auto* block : additions)
	{
		if (block->GetStatus() == Status::kInActive) continue;

		if (block->Getter_Trans()->pos.z >= min && block->Getter_Trans()->pos.z <= max )
		{
			block->rakka = true;
		}

		else
		{
			continue;
		}
	}


	mapLast += vanishNum;
	vanishNum = 0;
}


void BlockManager::MoveBlocks()
{
	auto wave = InGameController::cur_wave;
	auto phase = InGameController::cur_phase;
	int numBlocks;

	if (cur_set >= maxSet) return;
	if (addCnt.count > 0.0f)
	{
		return;
	}

	if (wave == 0 && phase == 0)
	{
		numBlocks = 8;
	}
	else if (wave == 0 && phase == 1)
	{
		numBlocks = 12;
	}

	else if (wave == 1 && phase == 0)
	{
		numBlocks = 20;
	}

	else if (wave == 1 && phase == 1)
	{
		numBlocks = 25;
	}

	int st = ((int)usingBlocks.size()) - cur_set * numBlocks - 1;
	for (int i = st; i > st - numBlocks; --i)
	{
		if (usingBlocks[i]->uwa == Uwa::kFall ||
			usingBlocks[i]->uwa == Uwa::kErase)
		{
			continue;
		}

		auto* trans = usingBlocks[i]->Getter_Trans();
		usingBlocks[i]->uwa = Uwa::kUsing;

		if (stopCnt.count == 0.0f)
		{
			trans->rotation.x = Easing::EaseInExpo(
				rotateNum * 90.0f, (rotateNum - 1.0f) * 90.0f, moveCnt.count);
			trans->pos.z = Easing::EaseInExpo(
				trans->prePos.z, trans->prePos.z - 1.0f, moveCnt.count);
		}
		else
		{
			trans->prePos = trans->pos;
		}
	}

	moveCnt.Add(0.0166666f);

	if (moveCnt.count >= 1.0f)
	{
		stopCnt.Add();
		if (stopCnt.IsEnd())
		{
			moveCnt.count = 0.0f;
			rotateNum++;
		}
	}
}

void BlockManager::Init()
{
	mapLast = 0;
	curLastPosZ = kStartPos.z;
	TurnBlocksIsActiveOff();
	SetAdditions();
	SetExceptAddtions();
	geneCnt.Initialize(4.0f);
	moveCnt.Initialize(0.75f); // 0.75f
	stopCnt.Initialize(0.5f);
	addCnt.Initialize(2.0f);
	sukoshiCnt.Initialize(1.25f);
	SetGround();

}

void BlockManager::Reset()
{
	curLastPosZ = kStartPos.z;
	mapLast = 0;
	cur_set = 0;
	rotateNum = 0;

	for (auto itr = normalBlocks.begin(); itr != normalBlocks.end(); ++itr)
	{
		(*itr)->SetStatus(Status::kInActive);
	}

	SetGround();
	geneCnt.count = 0.0f;
	moveCnt.count = 0.0f;
	stopCnt.count = 0.0f;
	addCnt.count = 0.0f;
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
			for (float y = 0; y < float(height); ++y, n++)
			{
				additions[n]->rakka = false;
				additions[n]->SetStatus(Status::kActive);
				additions[n]->Getter_Trans()->pos = kStartPos +
				Vector3{x, -y, z};

				mapOkuZ = additions[n]->Getter_Trans()->pos.z;
			}
		}
	}
}


void BlockManager::GenerateBlocks()
{
	if (!doGenerate) return;
	
	cur_set = 0;

	BlockManager::BlockGenerateData data = GetGenerateData();

	for (auto* block : usingBlocks)
	{
		block->Getter_Trans()->scale = { 1,1,1 };
		block->Getter_Trans()->rotation.x = 0.0f;
		block->Getter_Trans()->pos = {};
		block->SetStatus(Status::kInActive);
		block->uwa = Uwa::kNotUse;
	}

	usingBlocks.clear();

	int n_n = (int)data.normal.size();
	int nCnt = 0;
	for (auto* block : forUse)
	{
		if (nCnt >= n_n) break;
		if (block->GetStatus() == Status::kActive) continue;

		block->SetStatus(Status::kActive);
		block->Getter_Trans()->pos = data.normal[nCnt];
		block->Getter_Trans()->pos.y -= 1.25f;
		block->Getter_Trans()->prePos = block->Getter_Trans()->pos;
		block->Getter_Trans()->scale.x = 0.975f;
		block->uwa = Uwa::kNotUse;
		usingBlocks.emplace_back(reinterpret_cast<GameObject*>(block));
		nCnt++;
	}


	n_n = (int)data.black.size();
	nCnt = 0;
	for (auto* block : blackBlocks)
	{
		if (nCnt >= n_n) break;
		if (block->GetStatus() == Status::kActive) continue;

		block->SetStatus(Status::kActive);
		block->Getter_Trans()->pos = data.black[nCnt];
		block->Getter_Trans()->pos.y -= 1.25f;
		block->Getter_Trans()->prePos = block->Getter_Trans()->pos;
		block->Getter_Trans()->scale.x = 0.975f;
		block->uwa = Uwa::kNotUse;
		usingBlocks.emplace_back(reinterpret_cast<GameObject*>(block));
		nCnt++;
	}

	n_n = (int)data.green.size();
	nCnt = 0;
	for (auto block : greenBlocks)
	{
		if (nCnt >= n_n) break;
		if (block->GetStatus() == Status::kActive) continue;
		block->SetStatus(Status::kActive);
		block->Getter_Trans()->pos = data.green[nCnt];
		block->Getter_Trans()->pos.y -= 1.25f;
		block->Getter_Trans()->prePos = block->Getter_Trans()->pos;
		block->Getter_Trans()->scale.x = 0.975f;
		block->uwa = Uwa::kNotUse;
		usingBlocks.emplace_back(reinterpret_cast<GameObject*>(block));
		nCnt++;
	}

	geneCnt.count = 0.0f;
	doGenerate = false;

	std::sort(usingBlocks.begin(), usingBlocks.end(), [](GameObject* s1, GameObject* s2)
		{return s1->Getter_Trans()->pos.z > s2->Getter_Trans()->pos.z; });
}

void BlockManager::MakeBlockToEnter()
{
	float t = geneCnt.count;

	if (t >= 1.0f)
	{
		return;
	}

	geneCnt.Add(0.0166666f);

	int size = (int)((float)usingBlocks.size() * t * 1.5f);
	Benri::Max(size, (int)usingBlocks.size());
	float ymax = kStartPos.y + kBlockSize;
	float const upSpeed = 1.0f * 0.0166666f;

	for (int i = 0; i < size; ++i)
	{
		usingBlocks[i]->Getter_Trans()->pos.y += upSpeed;
		Benri::Max(usingBlocks[i]->Getter_Trans()->pos.y, ymax);
		usingBlocks[i]->Getter_Trans()->scale.x = Easing::Lerp(0.975f, 1.0f, t);
	}

}

BlockManager::BlockGenerateData BlockManager::GetGenerateData()
{
	auto wave = InGameController::cur_wave;
	auto phase = InGameController::cur_phase;
	BlockManager::BlockGenerateData data;
	float buff = mapOkuZ;

	int const numSet = 3;

	if (wave == 0 && phase == 0)
	{
		for (int p = 0; p < numSet; ++p)
		{
			int n = rand() % patternData.kNumPattern;

			for (int i = 0; i < 2; ++i, buff--)
			{
				for (int k = 0; k < 4; ++k)
				{
					int type = patternData.pattern0[n][i][k];
					if (type == 0)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						data.green.emplace_back(pos);
					}
					else if (type == 1)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						&data.normal.emplace_back(pos);
					}
					else
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						&data.black.emplace_back(pos);
					}

				}
			}
		}
	}
	else if (wave == 0 && phase == 1)
	{
		for (int p = 0; p < numSet; ++p)
		{
			int n = rand() % patternData.kNumPattern;

			for (int i = 0; i < 3; ++i, buff--)
			{
				for (int k = 0; k < 4; ++k)
				{
					int type = patternData.pattern1[n][i][k];
					if (type == 0)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						data.green.emplace_back(pos);
					}
					else if (type == 1)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						&data.normal.emplace_back(pos);
					}
					else
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						&data.black.emplace_back(pos);
					}
				}
			}
		}

	}

	else if (wave == 1 && phase == 0)
	{
		for (int p = 0; p < numSet; ++p)
		{
			int n = rand() % patternData.kNumPattern;

			for (int i = 0; i < 4; ++i, buff--)
			{
				for (int k = 0; k < 5; ++k)
				{
					int type = patternData.pattern2[n][i][k];
					if (type == 0)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						data.green.emplace_back(pos);
					}
					else if (type == 1)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						&data.normal.emplace_back(pos);
					}
					else
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						&data.black.emplace_back(pos);
					}

				}
			}
		}
	}

	else if (wave == 1 && phase == 1)
	{
		for (int p = 0; p < numSet; ++p)
		{
			for (int i = 0; i < 5; ++i, buff--)
			{
				for (int k = 0; k < 5; ++k)
				{
					int type = patternData.pattern3[p][i][k];
					if (type == 0)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						data.green.emplace_back(pos);
					}
					else if (type == 1)
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize ,
							buff
						};

						&data.normal.emplace_back(pos);
					}
					else
					{
						Vector3 pos =
						{
							kStartPos.x + float(k),
							kStartPos.y + kBlockSize,
							buff
						};

						&data.black.emplace_back(pos);
					}

				}
			}
		}

	}

	return data;
}

void BlockManager::AddBlockToLast()
{
	if (isPerfect != 1) return;
	addBlocks.clear();
	int n = 0;

	for (float z = 0; z < 1; ++z)
	{
		for (float x = 0; x < waveData[InGameController::cur_wave].startSize.x; ++x)
		{
			for (float y = 0; y < float(height); ++y, n++)
			{
				while (1)
				{
					if (additions[n]->GetStatus() == Status::kInActive)
					{
						break;
					}
					n++;
				}

				float const stPosOffsetZ = -1000.0f;
				Vector3 tmp = kStartPos + Vector3{ x, -y, stPosOffsetZ };

				additions[n]->addStartPos = tmp;
				additions[n]->Getter_Trans()->pos = tmp;
				addBlocks.emplace_back(additions[n]);
			}
		}
	}
	
}

void BlockManager::SetExceptAddtions()
{
	int n = 0;
	for (auto itr = normalBlocks.begin(); itr != normalBlocks.end(); ++itr)
	{
		if ((*itr)->forAddition) continue;
		forUse.emplace_back((*itr));
	}

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
	waveData[0].Init({ 4,16 }, { 128,128,128,255 });//16
	waveData[1].Init({ 5,26 }, { 128,128,128,255 }); // 26

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

bool BlockManager::IsFall(float const z_)
{
	float limitLine = (kStartPos.z - (-mapLast * kBlockSize) - kBlockSize * 0.65f) ;
	if (z_ <= limitLine)
	{
		return true;
	}

	return false;
}


bool BlockManager::CheckAllVanished()
{
	for (auto* block : usingBlocks)
	{
		if (block->uwa == Uwa::kUsing) return false ;
	}

	sukoshiCnt.Add();

	if (sukoshiCnt.count<1.0f)
	{
		return false;
	}

	return true;
}

bool BlockManager::CheckIsPerfect()
{
	for (auto* block : usingBlocks)
	{
		if (block->uwa == Uwa::kFall) return false;
	}

	for (auto* block : usingBlocks)
	{
		block->uwa = Uwa::kNotUse;
		block->Getter_Trans()->rotation.x = 0.0f;
	}

	isPerfect++;

	return true;

}

bool BlockManager::AddPerformance()
{
	if (addBlocks.empty())
	{
		rotateNum = 0;
		cur_set++;
		if (cur_set >= maxSet)
		{
			cur_set = 0;
			sukoshiCnt.count = 0.0f;
			InGameController::canChangeMode = true;
		}

		return false;
	}
	if (addCnt.count >= 1.0f) return false;

	addCnt.Add();

	if (addCnt.count <= 0.5f)
	{
		float t = Counter::GetNormalizedCount(0.0f, 0.5f, addCnt.count);

		float const offsetZ = kStartPos.z + (mapLast - 1.0f) * kBlockSize;

		for (auto* block : addBlocks)
		{
			block->SetStatus(Status::kActive);

			block->Getter_Trans()->pos.z =
				Easing::EaseOutSine(block->addStartPos.z, offsetZ, t);
		}
	}


	if (addCnt.IsEnd())
	{
		sukoshiCnt.count = 0.0f;
		addBlocks.clear();
		mapLast--;
		rotateNum = 0;
		isPerfect = 0;
		cur_set++;
		if (cur_set >= maxSet)
		{
			cur_set = 0;
			InGameController::canChangeMode = true;
		}


		return true;
	}


	
	return false;

}

void BlockManager::SetCollisionBackTable()
{

}