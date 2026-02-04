#include "BuildingsManager.h"
#include "../Enemy/EnemyFactory/EnemyFactory.h"
#include "../Enemy/EnemyTower/EnemyTower.h"
#include "../Player/PlayerTower/PlayerTower.h"
#include "../../Config/InGameConfig.h"

//コリジョンバックテーブルを設定
void BuildingsManager::SetCollisionBackTable()
{}

void BuildingsManager::LoadData()
{}

void BuildingsManager::SaveData()
{}

void BuildingsManager::DebugDraw()
{}

bool BuildingsManager::isClear() const
{
	bool allDestroyed = true;
	for (auto& tower : enemyTowers)
	{
		if (!tower->IsDead())
		{
			allDestroyed = false;
			break;
		}
	}
	return allDestroyed;
}

bool BuildingsManager::isGameOver() const
{
	bool allDestroyed = true;
	for (auto& pTower : playerTowers)
	{
		if (!pTower->IsDead())
		{
			allDestroyed = false;
			break;
		}
	}
	return allDestroyed;
}

void BuildingsManager::SetEnemyFactory(EnemyFactory* factory)
{
	enemyFactories.push_back(factory);
}

void BuildingsManager::SetEnemyTower(EnemyTower * tower)
{
	enemyTowers.push_back(tower);
}

void BuildingsManager::SetPlayerTower(PlayerTower * tower)
{
	playerTowers.push_back(tower);
}

void BuildingsManager::NotifyEnemyFactoryDead(EnemyFactory* factory)
{
	factory->rebornCounter.Initialize(inGameConfig->enemyFactoryRespawnInterval);
}

void BuildingsManager::ReplaceOnMap(const int32_t stage)
{
	for (auto& factory : enemyFactories)
	{
		factory->ReplaceOnMap(stage);
	}
	for (auto& tower : enemyTowers)
	{
		tower->ReplaceOnMap(stage);
	}
	for (auto& pTower : playerTowers)
	{
		pTower->ReplaceOnMap(stage);
	}
}

void BuildingsManager::Update()
{
	for (auto& factory : enemyFactories)
	{
		if (factory->IsDead())
		{
			factory->rebornCounter.Add();
			if (factory->rebornCounter.IsEnd())
			{
				factory->Reset();
			}
		}
	}
}

void BuildingsManager::Init()
{
}

void BuildingsManager::Reset()
{
}

void BuildingsManager::Draw(Matrix4* vpMat_)
{
}

void BuildingsManager::DrawHpBar(Matrix4* vpMat_)
{
	for (auto& factory : enemyFactories)
	{
		factory->DrawHpBar(vpMat_);
	}
	for (auto& tower : enemyTowers)
	{
		tower->DrawHpBar(vpMat_);
	}
	for (auto& pTower : playerTowers)
	{
		pTower->DrawHpBar(vpMat_);
	}
}


BuildingsManager::BuildingsManager()
{
}