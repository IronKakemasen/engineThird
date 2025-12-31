#include "GameObjectManager.h"
#include "../GameObject/GameObjectBehavior.h"

void GameObjectManager::RegisterForContainer(GameObject* dst_)
{
	objContainer.emplace_back(dst_);
}

void GameObjectManager::Init()
{
	for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
	{
		(*itr)->Init();
	}
}

void GameObjectManager::Reset()
{
	for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
	{
		(*itr)->Reset();
	}
}



void GameObjectManager::Update()
{
	for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
	{
		if ((*itr) == nullptr) continue;
		else if ((*itr)->GetStatus() == GameObjectBehavior::ObjectStatus::kInActive)
		{
			continue;
		}

		(*itr)->Update();
	}
}

void GameObjectManager::Render(Matrix4* vpMat_)
{
	for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
	{
		if ((*itr) == nullptr) continue;
		else if ((*itr)->GetStatus() == GameObjectBehavior::ObjectStatus::kInActive)
		{
			continue;
		}

		(*itr)->Draw(vpMat_);
	}

}
