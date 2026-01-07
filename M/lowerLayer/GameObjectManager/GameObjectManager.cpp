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
		(*itr)->colObj.clear();

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

		int g = 0;
		if (thisObj_->Getter_Identity()->tag == GameObject::Tag::kPlayer)
		{
			g = g;
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