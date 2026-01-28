#include "StageSelectScene.h"
#include "../../utilities/Json/Json.h"
#include <numbers>


void StageSelectScene::Update()
{
	if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	{
		Reset();
		gameObjManager->Reset();
		for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
		{
			for (size_t i = 0; i < player[stageIndex].size(); ++i)
			{
				player[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < grounds[stageIndex].size(); ++i)
			{
				grounds[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
			{
				playerTowers[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < allies[stageIndex].size(); ++i)
			{
				allies[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < playerBullets[stageIndex].size(); ++i)
			{
				playerBullets[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < enemies[stageIndex].size(); ++i)
			{
				enemies[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
			{
				enemyTowers[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
			for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
			{
				enemyFactories[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			}
		}
	}

	mainCamera.Update();

	// ステージセレクトの回転処理
	UpdateStageSelectRotation();

	// ステージ決定
	DecideStage();

	// 決定後演出
	UpdateAfterDecideStage();

	// ポストエフェクト
	AdaptToPostEffect();
}

void StageSelectScene::AdaptToPostEffect()
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

void StageSelectScene::UpdateStageSelectRotation()
{
	if (selected) return;

	bool right = false;
	bool left = false;

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		Vector2 dir = M::GetInstance()->getPadState.GetLeftStick(0);
		if (dir.x > 0.3f) right = true;
		else if (dir.x < -0.3f) left = true;

		if (M::GetInstance()->getPadState.IsHeld(0, PAD_RIGHT)) right = true;
		else if (M::GetInstance()->getPadState.IsHeld(0, PAD_LEFT)) left = true;
	}
	else
	{
		if (M::GetInstance()->IsKeyPressed(KeyType::RIGHT)) left = true;
		else if (M::GetInstance()->IsKeyPressed(KeyType::LEFT)) right = true;
	}

	if (selectCounter.count >= 1.0f)
	{
		if (right)
		{
			inGameController->curStage++;
			if (inGameController->curStage >= GameConstants::kMaxStages)
			{
				inGameController->curStage = 0;
			}
			startRotateY = baseCenterRotateY;
			targetRotateY = baseCenterRotateY + stagePerYRotate;
			selectCounter.Initialize(1.0f);
		}
		else if (left)
		{
			inGameController->curStage--;
			if (inGameController->curStage < 0)
			{
				inGameController->curStage = GameConstants::kMaxStages - 1;
			}
			startRotateY = baseCenterRotateY;
			targetRotateY = baseCenterRotateY - stagePerYRotate;
			selectCounter.Initialize(1.0f);
		}
	}

	const Vector2 baseDist = { 0.0f,50.0f };
	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		float rotateY = 180.0f + baseCenterRotateY + (stagePerYRotate * (GameConstants::kMaxStages - stageIndex));
		Vector3 dist = Vector3(baseDist.x, 0.0f, baseDist.y);
		dist.x = baseDist.x * std::cos(rotateY * std::numbers::pi_v<float> / 180.0f) - baseDist.y * std::sin(rotateY * std::numbers::pi_v<float> / 180.0f);
		dist.z = baseDist.x * std::sin(rotateY * std::numbers::pi_v<float> / 180.0f) + baseDist.y * std::cos(rotateY * std::numbers::pi_v<float> / 180.0f);
		centerObject[stageIndex][0]->trans.pos = dist;
	}

	// 補間
	baseCenterRotateY = Easing::EaseOutSine(startRotateY, targetRotateY, selectCounter.count);

	selectCounter.Add();
}

void StageSelectScene::DecideStage()
{
	if (selectCounter.count < 1.0f) return;

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		if (M::GetInstance()->getPadState.IsJustPressed(0, PAD_A))
		{
			selected = true;
			afterDecideCounter.Initialize(3.0f);
		}
	}
	else
	{
		if (M::GetInstance()->IsKeyTriggered(KeyType::SPACE))
		{
			selected = true;
			afterDecideCounter.Initialize(3.0f);
		}
	}
}

void StageSelectScene::UpdateAfterDecideStage()
{
	if (selected)
	{
		for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
		{
			if (stageIndex != static_cast<size_t>(inGameController->curStage))
			{
				centerObject[stageIndex][0]->trans.pos.y -= 0.5f;
			}
			else
			{
				float siko = (afterDecideCounter.count * 2.5f);
				if (siko > 1.0f) siko = 1.0f;
				centerObject[stageIndex][0]->trans.pos.y =
					std::sinf(siko * 3.14f) * 10;

				centerObject[stageIndex][0]->trans.rotation.y = 
					Easing::EaseOutSine(0.0f, 360.0f, siko);
			}
		}

		afterDecideCounter.Add();
		if (afterDecideCounter.IsEnd())
		{
			//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**+*+*+
			ChangeScene(SceneType::kInGame);
			//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**+*+*+
		}
	}
}

void StageSelectScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);



}

void StageSelectScene::Reset()
{
	mainCamera.Reset();
}

void StageSelectScene::Debug()
{
#ifdef USE_IMGUI

	ImGui::Begin("StageSelectScene");
	auto* para = mainCamera.cameraPara;


	ImGui::Text("---------------------------");
	ImGui::DragFloat3("cameraPos", reinterpret_cast<float*> (&para->trans.pos),0.1f);
	ImGui::DragFloat3("CameralookDir", reinterpret_cast<float*> (&para->trans.lookDir), 0.01f);
	ImGui::DragFloat("kaitenHokan", &para->trans.interpolationCoe, 0.01f);
	ImGui::DragFloat("FOV", &para->fov, 0.01f);



	ImGui::SliderInt("curStage", &inGameController->curStage, 0, GameConstants::kMaxStages - 1);
	ImGui::DragFloat("baseCenterRotateY", &baseCenterRotateY);

	ImGui::Text("---------------------------");
	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		std::string key = "stageIndex." + std::to_string(stageIndex) + "##CenterObject" + std::to_string(stageIndex);
		ImGui::DragFloat3((key + "rot").c_str(), &centerObject[stageIndex][0]->trans.rotation.x, 0.1f);
		ImGui::DragFloat3((key + "pos").c_str(), &centerObject[stageIndex][0]->trans.pos.x, 0.1f);
	}
	ImGui::End();

#endif // USE_IMGUI

}

