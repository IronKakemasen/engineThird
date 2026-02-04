#include "InGameScene.h"
#include "../../utilities/Json/Json.h"
#include "../../Systems/DamageDisplay/DamageDisplay.h"
#include "../../Systems/DeathParticle/DeathParticle.h"

void InGameScene::Update()
{
	if (uiDisplayer)
	{
		switch (uiDisplayer->GetPauseRequest())
		{
		case UIDisplayer::PauseRequest::kRetry:
			SceneBehavior::doReset = true;
			break;

		case UIDisplayer::PauseRequest::kBackToStageSelect:
			ChangeScene(SceneType::kStageSelect);
			SceneBehavior::doReset = true;
			break;

		case UIDisplayer::PauseRequest::kNone:
		default:
			break;
		}
	}

	switch (inGameController->curMode)
	{
	case InGameController::kEnter : 

		EnterMode();
		break;

	case InGameController::kPlayable:
		PlayableMode();
		break;

	case InGameController::kUnPlayable:

		break;

	case InGameController::kGameOver:

		break;

	case InGameController::kResult:

		break;

	}

	if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	{
		SceneBehavior::doReset = true;
	}

	mainCamera.Update();

	AdaptToPostEffect();

	DeathParticle::Get()->Update();
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
	std::vector<GameObject*> bullets = gameObjManager->Find(GameObject::kPlayerBullet);

	auto* dirPara = dirLight->Getter_Para();

	switch (curEffectType)
	{
	case PostEffectType::kNone:
	{
		ground->groundPlane->model->GetAppearance(0)->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");
		dirPara->intensity = dirLightIntensityNormal;
		dirPara->pos = dirLightDir;
		metalicCommon = metalicCommonNormal;
		roughnessCommon = roughnessCommonNormal;
		lightradiusCommon = 300.0f;

		break;
	}
	case PostEffectType::kGreyScale:
	{
		ground->groundPlane->model->GetAppearance(0)->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

		dirPara->intensity = dirLightIntensityNormal;
		dirPara->pos = dirLightDir;
		metalicCommon = metalicCommonNormal;
		roughnessCommon = roughnessCommonNormal;


		break;
	}
	case PostEffectType::kSimpleNeonLike:
	{
		auto* appe = ground->groundPlane->model->GetAppearance(0);
		appe->color = { 255,255,255,255 };
		appe->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

		dirPara->intensity = dirLightIntensityNeon;
		dirPara->pos = {10.4f,9.7f,0.0f};
		metalicCommon = metalicCommonNeon;
		roughnessCommon = roughnessCommonNeon;

		lightradiusCommon = 11.0f;
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
		for (auto* m : fac_->model->models)
		{
			auto* appe = m->GetAppearance(0);
			appe->metalic = metalicCommon;
			appe->roughness = roughnessCommon;

		}
	}

	//Enemy
	for (auto* alli : alliance)
	{
		auto* ally = reinterpret_cast<PlayerAlly*>(alli);		
		auto* appe = ally->model->model->GetAppearance(0);

		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	//PLayer
	auto* player_ = reinterpret_cast<Player*>(player);
	for (auto* m : player_->model->models)
	{
		m->GetAppearance(0)->metalic = metalicCommon;
		m->GetAppearance(0)->roughness = roughnessCommon;	
	}

	//Bullets
	for (auto* bullet : bullets)
	{
		auto* bullet_ = reinterpret_cast<PlayerBullet*>(bullet);
		auto* appe = bullet_->model->model->GetAppearance(0);

		appe->metalic = metalicCommon;
		appe->roughness = roughnessCommon;
	}

	//Ground
	ground->groundPlane->model->GetAppearance(0)->metalic = metalicCommon;
	ground->groundPlane->model->GetAppearance(0)->roughness = roughnessCommon;

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

	// HPバー描画
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->DrawHpBar(vpMat);
	}
	buildingsManager->DrawHpBar(vpMat);

	// フィールドライト描画
	for (int i = 0; i < kNumPLight; ++i)
	{
		auto* para = fieldpointLights[i]->Getter_Para();

		if (!para->isActive)continue;
		lightModels[i].Draw(vpMat);
	}

	// ダメージ表示描画
	DamageDisplay::Get()->Draw(&ortho);
	// デスパーティクル描画
	DeathParticle::Get()->Draw(vpMat);

	//// //UI描画
	uiDisplayer->SuperDraw(&ortho);
	uiDisplayer->DebugDraw();

	sprite_move.Draw(&ortho);
	sprite_shot.Draw(&ortho);
	sprite_reticle.Draw(&ortho);
	sprite_pause.Draw(&ortho);
	sprite_set.Draw(&ortho);
}

void InGameScene::Reset()
{
	mainCamera.Reset();

	uiDisplayer->SetUIMode(UIDisplayer::UIMode::InGame);
}

void InGameScene::Debug()
{
#ifdef USE_IMGUI

	ImGui::Begin("InGameController");
	ImGui::Text(("Mode  : " + inGameController->WathchInString()).c_str());
	ImGui::Text("Count : %.1f", *inGameController->GetCnt());
	ImGui::DragFloat4("ccc", reinterpret_cast<float*>(&player->model->cannon->GetAppearance(0)->color));
	ImGui::End();

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
		if (ImGui::BeginTabItem("Ground"))
		{
			ground->DebugDraw();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			player->DebugDraw();
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

	ImGui::Begin("InGameConfig");
	inGameConfig->DebugDraw();
	ImGui::End();

#endif // USE_IMGUI

}


void InGameScene::EnterMode()
{
	float cnt = inGameController->curCnt;

	int useNo{};
	std::vector<Vector3> dstPositions;

	//Player
	auto* playerLight = fieldpointLights[0]->Getter_Para();
	playerLight->intensity = 20000;
	playerLight->invSqrRadius = 60;
	dstPositions.emplace_back(Vector3{ 0,6.0f,-0.5f }.GetMultiply(player->Getter_Trans()->GetWorldMatrix()));
	playerLight->color = { 20,20,255 };

	useNo++;

	std::vector<GameObject*> ets = gameObjManager->Find(GameObject::kEnemyTower);
	std::vector<GameObject*> pts = gameObjManager->Find(GameObject::kPlayerTower);
	std::vector<GameObject*> alliance = gameObjManager->Find(GameObject::kPlayerAlly);
	std::vector<GameObject*> factories = gameObjManager->Find(GameObject::kEnemyFactory);

	//EnemyTower
	for (auto* enemyTower : ets)
	{
		if (enemyTower->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 800;
		dstPositions.emplace_back(Vector3{ 0.0f,6.0f,1.75f }.GetMultiply(enemyTower->Getter_Trans()->GetWorldMatrix()));
		enemyTowerLight->color = { 255,0,0 };

		useNo++;
	}

	//factories
	for (auto* factory_ : factories)
	{
		if (factory_->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 100;
		dstPositions.emplace_back(Vector3{ 0.0f,10,0 }.GetMultiply(factory_->Getter_Trans()->GetWorldMatrix()));
		enemyTowerLight->color = { 200,0,0 };

		useNo++;
	}


	//PlayerTower
	for (auto* pt_ : pts)
	{
		if (pt_->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 100;
		dstPositions.emplace_back(Vector3{ 0.0f,5.0f,-2.25f }.GetMultiply(pt_->Getter_Trans()->GetWorldMatrix()));
		enemyTowerLight->color = { 20,50,255 };

		useNo++;
	}


	for (int i = 0; i < (int)dstPositions.size(); ++i)
	{
		auto* para = fieldpointLights[i]->Getter_Para();
		para->isActive = true;

		Vector3 fstPos = dstPositions[i] + Vector3{0,-10,0};
		para->pos = Easing::EaseInOutQuad(fstPos, dstPositions[i], cnt);
	}
}

void InGameScene::PlayableMode()
{
	Lighthing();
	DamageDisplay::Get()->Update();
	static bool b = 1;
	if (b)
	{
		b = false;
		DeathParticle::Get()->Activate({ 0,5,5 }, 10, 1.0f, 1.0f, { 255,255,255 });
	}
}

void InGameScene::Lighthing()
{
	int useNo = 0;

	//Player
	auto* playerLight = fieldpointLights[0]->Getter_Para();
	playerLight->intensity = 10000;
	playerLight->invSqrRadius = 600;
	playerLight->pos =
		Vector3{ 0,6.0f,-0.5f }.GetMultiply(player->Getter_Trans()->GetWorldMatrix());
	playerLight->color = { 50,50,255 };

	useNo++;
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;

	std::vector<GameObject*> ets = gameObjManager->Find(GameObject::kEnemyTower);
	std::vector<GameObject*> pts = gameObjManager->Find(GameObject::kPlayerTower);
	std::vector<GameObject*> alliance = gameObjManager->Find(GameObject::kPlayerAlly);
	std::vector<GameObject*> factories = gameObjManager->Find(GameObject::kEnemyFactory);
	
	//EnemyTower
	for (auto* enemyTower : ets)
	{
		if (enemyTower->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 800;
		enemyTowerLight->pos =
			Vector3{ 0.0f,10,0 }.GetMultiply(enemyTower->Getter_Trans()->GetWorldMatrix());
		enemyTowerLight->color = { 255,0,0 };

		useNo++;
	}



	//factories
	for (auto* factory_ : factories)
	{
		if (factory_->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 100;
		enemyTowerLight->pos =
			Vector3{ 0.0f,10,0 }.GetMultiply(factory_->Getter_Trans()->GetWorldMatrix());
		enemyTowerLight->color = { 200,0,0 };

		useNo++;
	}


	//PlayerTower
	for (auto* pt_ : pts)
	{
		if (pt_->GetStatus() == GameObject::Status::kInActive) continue;
		auto* enemyTowerLight = fieldpointLights[useNo]->Getter_Para();
		enemyTowerLight->intensity = 20000;
		enemyTowerLight->invSqrRadius = 100;
		enemyTowerLight->pos =
		Vector3{0.0f,5.0f,-2.25f}.GetMultiply(pt_->Getter_Trans()->GetWorldMatrix());
		enemyTowerLight->color = { 20,50,255 };

		useNo++;
	}

}