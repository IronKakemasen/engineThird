#include "BuildingsManager.h"

//コリジョンバックテーブルを設定
void BuildingsManager::SetCollisionBackTable()
{}

void BuildingsManager::LoadData()
{}

void BuildingsManager::SaveData()
{}

void BuildingsManager::DebugDraw()
{}

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

void BuildingsManager::ReplaceOnMap(const int32_t stage)
{}

void BuildingsManager::Update()
{
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


BuildingsManager::BuildingsManager()
{
}