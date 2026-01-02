#include "GameObjectManager.h"
#include "../GameObject/GameObjectBehavior.h"
#include "imgui.h"

void GameObjectManager::RegisterForContainer(GameObject* dst_)
{
	objContainer.emplace_back(dst_);
	dst_->SetNumber(createNum++);
}

void GameObjectManager::Debug()
{
#ifdef USE_IMGUI

	ImGui::Begin("ObjManager");

	if (ImGui::TreeNode("All"))
	{
		for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
		{
			if ((*itr) == nullptr) continue;

			if (ImGui::TreeNode((*itr)->Getter_Name().c_str()))
			{
				ImGui::DragFloat3("pos", reinterpret_cast<float*>(&(*itr)->Getter_Trans()->pos), 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	else if (ImGui::TreeNode("Active"))
	{
		for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
		{
			if ((*itr) == nullptr) continue;
			else if ((*itr)->GetStatus() == GameObjectBehavior::Status::kInActive) continue;

			if (ImGui::TreeNode((*itr)->Getter_Name().c_str()))
			{
				ImGui::DragFloat3("pos", reinterpret_cast<float*>(&(*itr)->Getter_Trans()->pos), 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	else if (ImGui::TreeNode("inActive"))
	{
		for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
		{
			if ((*itr) == nullptr) continue;
			else if ((*itr)->GetStatus() == GameObjectBehavior::Status::kActive) continue;

			if (ImGui::TreeNode((*itr)->Getter_Name().c_str()))
			{
				ImGui::DragFloat3("pos", reinterpret_cast<float*>(&(*itr)->Getter_Trans()->pos), 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();

	}
	ImGui::End();

#endif
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
		else if ((*itr)->GetStatus() == GameObjectBehavior::Status::kInActive)
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
		else if ((*itr)->GetStatus() == GameObjectBehavior::Status::kInActive)
		{
			continue;
		}

		(*itr)->Draw(vpMat_);
	}

}
