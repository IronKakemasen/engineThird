#include "InGameScene.h"
#include "../../utilities/Json/Json.h"

void InGameScene::Update()
{
	////アトラス画像の更新
	//atlasNumber.Update();
	////実践
	//static Counter timer(1.0f);
	//static float timeNum;
	//timer.Add();
	//if (timer.IsEnd())
	//{
	//	timeNum++;
	//	Benri::AdjustMax(timeNum, 9.0f, 0.0f);
	//}
	//atlasNumber.ChangeAtlasIndex(timeNum);

	if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	{
		SceneBehavior::doReset = true;
	}

	mainCamera.Update();

	AdaptToPostEffect();

	auto* rPara = pointLights[0]->Getter_Para();
	//rPara->pos = player->Getter_Trans()->GetWorldPos();
	//rPara->pos.y += 1.5f; rPara->intensity = intensityCommon;

	ImGui::Begin("Dian");
	ImGui::DragFloat("intensityCommon", &intensityCommon);
	ImGui::DragFloat("radius", &rPara->invSqrRadius);
	ImGui::DragFloat3("pos", reinterpret_cast<float*>(&rPara->pos),0.1f);
	ImGui::End();

	rPara->intensity = intensityCommon;

	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;

	M::GetInstance()->DrawEllipseWireFrame(rPara->pos, 0.5f,
		{ 90,0,0 }, { 255,255,255,255 }, vpMat);
}

void InGameScene::AdaptToPostEffect()
{
	auto effectType = M::GetInstance()->WatchEffectType();
	if (curEffectType == effectType) return;
	curEffectType = effectType;

	std::vector<GameObject*> enemies = gameObjManager->Find(GameObject::kEnemy);
	GameObject* player = gameObjManager->Find(GameObject::kPlayer)[0];
	std::vector<GameObject*> ets = gameObjManager->Find(GameObject::kEnemyTower);
	std::vector<GameObject*> pts = gameObjManager->Find(GameObject::kPlayerTower);
	std::vector<GameObject*> alliance = gameObjManager->Find(GameObject::kPlayerAlly);
	std::vector<GameObject*> factories = gameObjManager->Find(GameObject::kEnemyFactory);

	auto* dirPara = dirLight->Getter_Para();

	switch (curEffectType)
	{
	case PostEffectType::kNone:
	{
		dirPara->intensity = dirLightIntensityNormal;
		dirPara->pos = dirLightDir;
		metalicCommon = metalicCommonNormal;
		roughnessCommon = roughnessCommonNormal;

		break;
	}
	case PostEffectType::kGreyScale:
	{
		dirPara->intensity = dirLightIntensityNormal;
		dirPara->pos = dirLightDir;
		metalicCommon = metalicCommonNormal;
		roughnessCommon = roughnessCommonNormal;

		break;
	}
	case PostEffectType::kSimpleNeonLike:
	{
		dirPara->intensity = dirLightIntensityNeon;
		dirPara->pos = {1.0f,0.1f,0.0f};
		metalicCommon = metalicCommonNeon;
		roughnessCommon = roughnessCommonNeon;

		break;
	}
	}

	//Enemy
	for (auto* e : enemies)
	{
		auto* enemy = reinterpret_cast<Enemy*>(e);
		for (auto* m : enemy->model->models)
		{
			m->GetAppearance(0)->metalic = metalicCommon;
			m->GetAppearance(0)->roughness = roughnessCommon;
		}
	}

	//ETower
	for (auto* enemyTower : ets)
	{
		auto* enemeyTower_ = reinterpret_cast<EnemyTower*>(enemyTower);
		auto* appe = enemeyTower_->model->model->GetAppearance(0);
		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	//PTower
	for (auto* playerTower : pts)
	{
		auto* playerTower_ = reinterpret_cast<PlayerTower*>(playerTower);
		auto* appe = playerTower_->model->model->GetAppearance(0);
		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	//Factory
	for (auto* fac : factories)
	{
		auto* fac_ = reinterpret_cast<EnemyFactory*>(fac);
		auto* appe = fac_->model->model->GetAppearance(0);
		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	//Enemy
	for (auto* alli : alliance)
	{
		auto* ally = reinterpret_cast<PlayerAlly*>(alli);		
		auto* appe = ally->model->model->GetAppearance(0);

		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	auto* player_ = reinterpret_cast<Player*>(player);
	for (auto* m : player_->model->models)
	{
		m->GetAppearance(0)->metalic = metalicCommon;
		m->GetAppearance(0)->roughness = roughnessCommon;	
	}

}

void InGameScene::Load()
{
	std::string key = "/ID/";
	Json::LoadParam(path, key + "dirLightIntensityNormal", dirLightIntensityNormal);
	Json::LoadParam(path, key + "dirLightIntensityNeon", dirLightIntensityNeon);
	Json::LoadParam(path, key + "dirLightDir", dirLightDir);
	Json::LoadParam(path, key + "metalicCommonNormal", metalicCommonNormal);
	Json::LoadParam(path, key + "roughnessCommonNormal", roughnessCommonNormal);
	Json::LoadParam(path, key + "metalicCommonNeon", metalicCommonNeon);
	Json::LoadParam(path, key + "roughnessCommonNeon", roughnessCommonNeon);

	metalicCommon = metalicCommonNeon;
	roughnessCommon = roughnessCommonNeon;
}


void InGameScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	uiDisplayer->SuperDraw(&ortho);
	uiDisplayer->DebugDraw();
}

void InGameScene::Reset()
{
	mainCamera.Reset();

	uiDisplayer->SetUIMode(UIDisplayer::UIMode::InGame);
}

void InGameScene::Debug()
{
#ifdef USE_IMGUI

	//ImGui::Begin("InGameController");
	//ImGui::Text(("Mode  : " + inGameController->WathchInString()).c_str());
	//ImGui::Text("Count : %.1f", *inGameController->GetCnt());
	//ImGui::End();

	//ImGui::Begin("Object Debug");

	//if (ImGui::BeginTabBar("Object Map", ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable))
	//{
	//	if (ImGui::BeginTabItem("EnemyFactory"))
	//	{
	//		int32_t Sum = 0;
	//		for (auto& factory : enemyFactories)
	//		{
	//			if (factory->GetStatus() == GameObjectBehavior::Status::kActive)
	//			{
	//				Sum++;
	//			}
	//		}

	//		if (ImGui::Button("Add"))
	//		{
	//			enemyFactories[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Remove"))
	//		{
	//			if (Sum > 0)
	//			{
	//				enemyFactories[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
	//			}
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Save"))
	//		{
	//			std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
	//			std::string path = enemyFactories[0]->path;

	//			Json::SaveParam(path, key, Sum);

	//			for (auto& factory : enemyFactories)
	//			{
	//				factory->SaveData();
	//			}
	//		}
	//		ImGui::Text("-----------------------------------");
	//		for (auto& factory : enemyFactories)
	//		{
	//			factory->DebugDraw();
	//		}

	//		ImGui::EndTabItem();
	//	}
	//	if (ImGui::BeginTabItem("PlayerTower"))
	//	{
	//		int32_t Sum = 0;
	//		for (auto& tower : playerTowers)
	//		{
	//			if (tower->GetStatus() == GameObjectBehavior::Status::kActive)
	//			{
	//				Sum++;
	//			}
	//		}
	//		if (ImGui::Button("Add"))
	//		{
	//			playerTowers[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Remove"))
	//		{
	//			if (Sum > 0)
	//			{
	//				playerTowers[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
	//			}
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Save"))
	//		{
	//			std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
	//			std::string path = playerTowers[0]->path;

	//			Json::SaveParam(path, key, Sum);

	//			for (auto& tower : playerTowers)
	//			{
	//				tower->SaveData();
	//			}
	//		}
	//		ImGui::Text("-----------------------------------");
	//		for (auto& tower : playerTowers)
	//		{
	//			tower->DebugDraw();
	//		}
	//		ImGui::EndTabItem();
	//	}
	//	if (ImGui::BeginTabItem("EnemyTower"))
	//	{
	//		int32_t Sum = 0;
	//		for (auto& tower : enemyTowers)
	//		{
	//			if (tower->GetStatus() == GameObjectBehavior::Status::kActive)
	//			{
	//				Sum++;
	//			}
	//		}
	//		if (ImGui::Button("Add"))
	//		{
	//			enemyTowers[Sum]->SetStatus(GameObjectBehavior::Status::kActive);
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Remove"))
	//		{
	//			if (Sum > 0)
	//			{
	//				enemyTowers[Sum - 1]->SetStatus(GameObjectBehavior::Status::kInActive);
	//			}
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Save"))
	//		{
	//			std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount";
	//			std::string path = enemyTowers[0]->path;
	//			Json::SaveParam(path, key, Sum);
	//			for (auto& tower : enemyTowers)
	//			{
	//				tower->SaveData();
	//			}
	//		}
	//		ImGui::Text("-----------------------------------");
	//		for (auto& tower : enemyTowers)
	//		{
	//			tower->DebugDraw();
	//		}
	//		ImGui::EndTabItem();
	//	}

	//	ImGui::EndTabBar();
	//}

	//ImGui::End();

	//ImGui::Begin("Object ");

	//if (ImGui::BeginTabBar("Object HP", ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable))
	//{
	//	ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Player         HP : %f", player->GetHP());
	//	for (int32_t i = 0; i < playerTowers.size(); ++i)
	//	{
	//		if (playerTowers[i]->GetStatus() == GameObjectBehavior::Status::kActive)
	//		{
	//			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "PlayerTower    HP : %f", playerTowers[i]->GetHP());
	//		}
	//	}
	//	for (int32_t i = 0; i < enemyTowers.size(); ++i)
	//	{
	//		if (enemyTowers[i]->GetStatus() == GameObjectBehavior::Status::kActive)
	//		{
	//			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "EnemyTower     HP : %f", enemyTowers[i]->GetHP());
	//		}
	//	}
	//	for (int32_t i = 0; i < enemyFactories.size(); ++i)
	//	{
	//		if (enemyFactories[i]->GetStatus() == GameObjectBehavior::Status::kActive)
	//		{
	//			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "EnemyFactory   HP : %f", enemyFactories[i]->GetHP());
	//		}
	//	}

	//	ImGui::EndTabBar();
	//}
	//ImGui::End();

ImGui::Begin("playerAttackGauge");
	//if (ImGui::BeginTabBar("Player"))
	{
		player->DebugDraw();
		//ImGui::EndTabBar();
	}

	ImGui::End();


	//ImGui::Begin("InGameConfig");
	//inGameConfig->DebugDraw();
	//ImGui::End();



#endif // USE_IMGUI

}


