#include "InGameScene.h"
#include "../../utilities/Json/Json.h"

void InGameScene::Update()
{
	//アトラス画像の更新
	atlasNumber.Update();
	//実践
	static Counter timer(1.0f);
	static float timeNum;
	timer.Add();
	if (timer.IsEnd())
	{
		timeNum++;
		Benri::AdjustMax(timeNum, 9.0f, 0.0f);
	}
	atlasNumber.ChangeAtlasIndex(timeNum);

	if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	{
		SceneBehavior::doReset = true;
	}

	mainCamera.Update();

	AdaptToPostEffect();
}

void InGameScene::AdaptToPostEffect()
{
	auto effectType = M::GetInstance()->WatchEffectType();
	auto* dirPara = dirLight->Getter_Para();

	switch (effectType)
	{
	case PostEffectType::kNone:
		dirPara->intensity = 1.0f;

		break;

	case PostEffectType::kGreyScale:
		dirPara->intensity = 1.0f;

		break;

	case PostEffectType::kSimpleNeonLike:
		dirPara->intensity = 12.0f;

		break;
	}
}

void InGameScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
}

void InGameScene::Reset()
{
	mainCamera.Reset();
}

void InGameScene::Debug()
{
#ifdef USE_IMGUI



	ImGui::Begin("InGameController");
	ImGui::Text(("Mode  : " + inGameController->WathchInString()).c_str());
	ImGui::Text("Count : %.1f", *inGameController->GetCnt());
	ImGui::End();


	for (int i = 0; i < 2; ++i)
	{
		auto* r = rectLights[i]->Getter_Para();
		ImGui::Begin(("RectLight" + std::to_string(i)).c_str());
		ImGui::DragFloat("intensity", &r->intensity);
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&r->pos));
		ImGui::DragFloat3("lookDir", reinterpret_cast<float*>(rectLights[i]->GetLookDirection()), 0.02f);
		ImGui::DragFloat3("color", reinterpret_cast<float*>(&r->color));
		ImGui::DragFloat("rad", &r->attenuationRadius);

		ImGui::End();

	}

	ImGui::Begin("Object Debug");

	if (ImGui::BeginTabBar("Object Map", ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable))
	{
		if (ImGui::BeginTabItem("EnemyFactory"))
		{
			int32_t Sum = 0;
			for (auto& factory : enemyFactories)
			{
				if (factory->GetStatus() == GameObjectBehavior::Status::kActive)
				{
					Sum++;
				}
			}

			if (ImGui::Button("Add"))
			{
				enemyFactories[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove"))
			{
				if (Sum > 0)
				{
					enemyFactories[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
				std::string path = enemyFactories[0]->path;

				Json::SaveParam(path, key, Sum);

				for (auto& factory : enemyFactories)
				{
					factory->SaveData();
				}
			}
			ImGui::Text("-----------------------------------");
			for (auto& factory : enemyFactories)
			{
				factory->DebugDraw();
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("PlayerTower"))
		{
			int32_t Sum = 0;
			for (auto& tower : playerTowers)
			{
				if (tower->GetStatus() == GameObjectBehavior::Status::kActive)
				{
					Sum++;
				}
			}
			if (ImGui::Button("Add"))
			{
				playerTowers[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove"))
			{
				if (Sum > 0)
				{
					playerTowers[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
				std::string path = playerTowers[0]->path;

				Json::SaveParam(path, key, Sum);

				for (auto& tower : playerTowers)
				{
					tower->SaveData();
				}
			}
			ImGui::Text("-----------------------------------");
			for (auto& tower : playerTowers)
			{
				tower->DebugDraw();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("EnemyTower"))
		{
			int32_t Sum = 0;
			for (auto& tower : enemyTowers)
			{
				if (tower->GetStatus() == GameObjectBehavior::Status::kActive)
				{
					Sum++;
				}
			}
			if (ImGui::Button("Add"))
			{
				enemyTowers[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove"))
			{
				if (Sum > 0)
				{
					enemyTowers[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
				std::string path = enemyTowers[0]->path;
				Json::SaveParam(path, key, Sum);
				for (auto& tower : enemyTowers)
				{
					tower->SaveData();
				}
			}
			ImGui::Text("-----------------------------------");
			for (auto& tower : enemyTowers)
			{
				tower->DebugDraw();
			}
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();

	ImGui::Begin("Object ");

	if (ImGui::BeginTabBar("Object HP", ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable))
	{
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Player         HP : %f", player->GetHP());
		for (int32_t i = 0; i < playerTowers.size(); ++i)
		{
			if (playerTowers[i]->GetStatus() == GameObjectBehavior::Status::kActive)
			{
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "PlayerTower    HP : %f", playerTowers[i]->GetHP());
			}
		}
		for (int32_t i = 0; i < enemyTowers.size(); ++i)
		{
			if (enemyTowers[i]->GetStatus() == GameObjectBehavior::Status::kActive)
			{
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "EnemyTower     HP : %f", enemyTowers[i]->GetHP());
			}
		}
		for (int32_t i = 0; i < enemyFactories.size(); ++i)
		{
			if (enemyFactories[i]->GetStatus() == GameObjectBehavior::Status::kActive)
			{
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "EnemyFactory   HP : %f", enemyFactories[i]->GetHP());
			}
		}

		ImGui::EndTabBar();
	}
	ImGui::End();

	ImGui::Begin("Object de");
	if (ImGui::BeginTabBar("Player"))
	{
		player->DebugDraw();
		ImGui::EndTabBar();
	}

	ImGui::End();


	ImGui::Begin("InGameConfig");
	inGameConfig->DebugDraw();
	ImGui::End();


	//ImGui::Begin("EnemyFactory");
	//auto drawList = ImGui::GetWindowDrawList();
	//drawList->AddRectFilled(ImVec2(10, 10), ImVec2(110, 110), IM_COL32(255, 0, 0, 255));
	//ImGui::End();


#endif // USE_IMGUI

}


