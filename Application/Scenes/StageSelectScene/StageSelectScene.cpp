#include "StageSelectScene.h"
#include "../../utilities/Json/Json.h"
#include <numbers>

void StageSelectScene::Update()
{

	if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	{
		SceneBehavior::doReset = true;
	}


	// ステージセレクトの回転処理
	UpdateStageSelectRotation();

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
	bool right = false;
	bool left = false;

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		Vector2 dir = M::GetInstance()->getPadState.GetLeftStick(0);
		if (dir.x > 0.3f) right = true;
		else if (dir.x < -0.3f) left = true;
	}
	else
	{
		if (M::GetInstance()->IsKeyPressed(KeyType::RIGHT)) right = true;
		else if (M::GetInstance()->IsKeyPressed(KeyType::LEFT)) left = true;
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

	mainCamera.Update();


	const Vector2 baseDist = { 0.0f,50.0f };
	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		float rotateY = 180.0f + baseCenterRotateY + (stagePerYRotate * stageIndex);
		Vector3 dist = Vector3(baseDist.x, 0.0f, baseDist.y);
		dist.x = baseDist.x * std::cos(rotateY * std::numbers::pi_v<float> / 180.0f) - baseDist.y * std::sin(rotateY * std::numbers::pi_v<float> / 180.0f);
		dist.z = baseDist.x * std::sin(rotateY * std::numbers::pi_v<float> / 180.0f) + baseDist.y * std::cos(rotateY * std::numbers::pi_v<float> / 180.0f);
		centerObject[stageIndex][0]->trans.pos = dist;
	}

	// 補間
	baseCenterRotateY = Easing::EaseOutSine(startRotateY, targetRotateY, selectCounter.count);

	selectCounter.Add();
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

	ImGui::Text("---------------------------");
	ImGui::DragFloat3("cameraPos", &mainCamera.cameraPara->trans.pos.x);
	ImGui::DragFloat3("cameraRot", &mainCamera.cameraPara->trans.rotation.x, 0.1f);



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


