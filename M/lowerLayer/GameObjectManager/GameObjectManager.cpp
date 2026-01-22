#include "GameObjectManager.h"
#include "../GameObject/GameObjectBehavior.h"
#include "../Collision/CollisionDetection/CollisionDetection.h"
#include "../../M.h"

#ifdef USE_IMGUI
#include "imgui.h"
#endif

#ifdef _DEBUG
void GameObjectManager::ForDebug::DrawCollider(GameObject* obj_, Matrix4* vpMat_)
{
	if (collisionVisibility)
	{
		if (!obj_->IsCollisionActivated()) return;

		if (obj_->HasRectCollider())
		{
			Vector3 world = obj_->Getter_Trans()->GetWorldPos();
			Rect r = obj_->Getter_Rect()->ConvertToWorld(world);
			Vector3 LT = { r.left,0,r.top };
			Vector3 RT = { r.right,0,r.top };
			Vector3 RB = { r.right,0,r.bottom };
			Vector3 LB = { r.left,0,r.bottom };

			M::GetInstance()->DrawLine(LT, RT,
				obj_->forDebug.colorForCollision, vpMat_);
			M::GetInstance()->DrawLine(RT, RB,
				obj_->forDebug.colorForCollision, vpMat_);
			M::GetInstance()->DrawLine(RB, LB,
				obj_->forDebug.colorForCollision, vpMat_);
			M::GetInstance()->DrawLine(LB, LT,
				obj_->forDebug.colorForCollision, vpMat_);
		}

		if (obj_->HasCircleCollider())
		{
			Vector3 world = obj_->Getter_Trans()->GetWorldPos();
			Circle* c = obj_->Getter_Circle();

			M::GetInstance()->DrawEllipseWireFrame(world, c->radius,
				{ 90.0f,0,0 }, obj_->forDebug.colorForCollision, vpMat_);
		}

	}
}

GameObjectManager::ForDebug::ForDebug()
{
	collisionVisibility = true;
}

#endif


void GameObjectManager::RegisterForContainer(GameObject* dst_)
{
	dst_->SetGameObjectManager(this);
	dst_->SetNumber(createNum++);

	objContainer.emplace_back(dst_);
}

std::vector<GameObject*> GameObjectManager::Find(GameObject::Tag tag_)
{
	std::vector<GameObject*> data;
	for (auto* i : objContainer)
	{
		if (i->Getter_Identity()->tag == tag_)
		{
			data.emplace_back(i);
		}
	}

	return data;
}

void GameObjectManager::Debug()
{
#ifdef USE_IMGUI
	static int selec = 0;

	ImGui::Begin("ObjManager", nullptr, ImGuiWindowFlags_MenuBar);

	ImGui::Text("CollisionVisivility : "); ImGui::SameLine();
	ImGui::Checkbox(" ", &forDebug.collisionVisibility);

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
		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 250), ImGuiWindowFlags_NoTitleBar);

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

#ifdef _DEBUG
		forDebug.DrawCollider((*itr), vpMat_);
#endif // _DEBUG

	}
}

void GameObjectManager::ChackAllCollision(GameObject* thisObj_)
{
	if (!thisObj_->IsCollisionActivated()) return;
	else if (!thisObj_->HasCollider()) return;

#ifdef _DEBUG
	thisObj_->forDebug.colorForCollision = { 50,50,200,255 };
#endif // _DEBUG

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
		else if (thisObj_->IsCollisionMaskMatched(otherObj->Getter_Identity()))
		{
			continue;
		}

		//ワールド座標を取得
		Vector3 thisWorldPos = thisObj_->Getter_Trans()->GetWorldPos();
		Vector3 otherWorldPos = otherObj->Getter_Trans()->GetWorldPos();

		//さーくるコリジョン
		if (thisObj_->HasCircleCollider() && otherObj->HasCircleCollider())
		{ 
			if (CollisionDetections::C2D::CircleCollision(
				thisObj_->Getter_Circle()->radius, thisWorldPos,
				otherObj->Getter_Circle()->radius, otherWorldPos))
			{
				thisObj_->SetCollidedObjPtr(otherObj);
				thisObj_->ActivateOnTriggerEnter(otherObj->Getter_Identity()->tag);
			}
		}
		//クアッドコリジョン
		else if (thisObj_->HasRectCollider() && otherObj->HasRectCollider())
		{
			if (CollisionDetections::C2D::ObjectAABB(
				thisObj_->Getter_Rect(), thisWorldPos,
				otherObj->Getter_Rect(), otherWorldPos))
			{
				thisObj_->SetCollidedObjPtr(otherObj);
				thisObj_->ActivateOnTriggerEnter(otherObj->Getter_Identity()->tag);
			}
		}


	}
}