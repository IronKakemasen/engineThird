#include "GameObjectManager.h"
#include "../GameObject/GameObjectBehavior.h"
#include "../Collision/CollisionDetection/CollisionDetection.h"
#ifdef USE_IMGUI
#include "imgui.h"
#endif

void GameObjectManager::RegisterForContainer(GameObject* dst_)
{
	objContainer.emplace_back(dst_);
	dst_->SetNumber(createNum++);
}

void GameObjectManager::Debug()
{
#ifdef USE_IMGUI
	static int selec = 0;

	ImGui::Begin("ObjManager", nullptr, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar()) 
	{
		if (ImGui::BeginMenu("Select Status"))
		{
			if (ImGui::MenuItem("Active")) 
			{
				selec = 0;
			}
			else if (ImGui::MenuItem("InActive"))
			{
				selec = 1;
			}
			else if (ImGui::MenuItem("All"))
			{
				selec = 2; 
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (selec == 0)
	{
		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

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
		ImGui::EndChild();
	}
	else if (selec == 1)
	{
		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

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
		ImGui::EndChild();

	}
	else
	{
		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
		for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
		{
			if ((*itr) == nullptr) continue;

			if (ImGui::TreeNode((*itr)->Getter_Name().c_str()))
			{
				ImGui::DragFloat3("pos", reinterpret_cast<float*>(&(*itr)->Getter_Trans()->pos), 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::EndChild();


	}

	ImGui::End();

#endif
}
void GameObjectManager::Init()
{
	for (auto itr = objContainer.begin(); itr != objContainer.end(); ++itr)
	{
		(*itr)->Init();
		(*itr)->SetCollisionBackTable();
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
		ChackAllCollision((*itr));
		(*itr)->UpdateCollisionBack();
		(*itr)->Getter_ColObj()->clear();

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

void GameObjectManager::ChackAllCollision(GameObject* thisObj_)
{
	if (!thisObj_->IsCollisionActivated()) return;
	else if (!thisObj_->HasCollider()) return;


	for (auto* otherObj : objContainer)
	{
		if (!otherObj->HasCollider()) continue;
		else if (!otherObj->IsCollisionActivated()) continue;

		//衝突相手がアクティブでなければ
		if (otherObj->GetStatus() == GameObject::Status::kInActive)
		{
			continue;
		}
		//マスク処理
		else if (!(thisObj_->IsCollisionMaskMatched(otherObj->Getter_Identity())))
		{
			continue;
		}

		//ワールド座標を取得
		Vector3 thisWorldPos = thisObj_->Getter_Trans()->GetWorldPos();
		Vector3 otherWorldPos = otherObj->Getter_Trans()->GetWorldPos();

		//クアッドコリジョン
		if (CollisionDetections::C2D ::ObjectAABB(
			thisObj_->Getter_Rect(), thisWorldPos,
			otherObj->Getter_Rect(), otherWorldPos))
		{
			//双方のオブジェクトの衝突反応関数をアクティブ化する
			thisObj_->ActivateOnTriggerEnter(otherObj->Getter_Identity()->tag);
			otherObj->ActivateOnTriggerEnter(thisObj_->Getter_Identity()->tag);

			//双方のオブジェクトの衝突相手を登録する
			thisObj_->SetCollidedObjPtr(otherObj);
			otherObj->SetCollidedObjPtr(thisObj_);

		}
	}
}