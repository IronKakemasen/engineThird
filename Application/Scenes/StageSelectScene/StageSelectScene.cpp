#include "StageSelectScene.h"
#include "../../utilities/Json/Json.h"
#include <numbers>


void StageSelectScene::Update()
{
	dirLight->Getter_Para()->pos = { 6.1f,0.5f,-20.0f };

	mainCamera.Update();

	// initializedがfalseならオブジェクト配置
	ReplaceObjects();

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

	Vector2 dir = M::GetInstance()->getPadState.GetLeftStick(0);
	if (dir.x > inGameConfig->deadZone) right = true;
	else if (dir.x < -inGameConfig->deadZone) left = true;

	if (M::GetInstance()->getPadState.IsHeld(0, PAD_RIGHT)) right = true;
	else if (M::GetInstance()->getPadState.IsHeld(0, PAD_LEFT)) left = true;

#ifdef _DEBUG
	if (M::GetInstance()->IsKeyPressed(KeyType::RIGHT)) left = true;
	else if (M::GetInstance()->IsKeyPressed(KeyType::LEFT)) right = true;
#endif // _DEBUG


	if (selectCounter.count >= 1.0f)
	{
		if (left)
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
		else if (right)
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

	const Vector2 baseDist = { 0.0f,100.0f };
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
	if (selected) return;

	if (selectCounter.count < 1.0f) return;

	bool decide = false;
	if (M::GetInstance()->getPadState.IsJustPressed(0, PAD_A)) decide = true;
	if (M::GetInstance()->getPadState.IsJustPressed(0, PAD_RB)) decide = true;
#ifdef _DEBUG
	if (M::GetInstance()->IsKeyTriggered(KeyType::SPACE))decide = true;
#endif // _DEBUG

	if (decide)
	{
		selected = true;
		afterDecideCounter.Initialize(2.0f);
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
				centerObject[stageIndex][0]->trans.pos.y -= 1.0f;
			}
			else
			{
				float siko = (afterDecideCounter.count * 2.2f);
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

	uiDisplayer->SuperDraw(&ortho);
	uiDisplayer->DebugDraw();
	DrawUI(vpMat);
}

void StageSelectScene::DrawUI(Matrix4* vpMat_)
{
	Matrix4 orth = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
	// ステージ名表示
	if (selected)
	{
		Vector3 displayPos = centerObject[inGameController->curStage][0]->Getter_Trans()->GetWorldPos();
		displayPos.y += 17.0f;
		Vector2 pos = ConvertToScreen(displayPos, *vpMat_);
		stageName[inGameController->curStage]->GetAppearance()->trans.pos = Vector3(pos.x, pos.y + 30.0f, 0.0f);
		stageName[inGameController->curStage]->Draw(&orth);
	}
	else
	{
		for (size_t i = 0; i < GameConstants::kMaxStages; ++i)
		{
			Vector3 displayPos = centerObject[i][0]->Getter_Trans()->GetWorldPos();
			displayPos.y += 17.0f;
			Vector2 pos = ConvertToScreen(displayPos, *vpMat_);
			stageName[i]->GetAppearance()->trans.pos = Vector3(pos.x, pos.y + 30.0f, 0.0f);
			stageName[i]->Draw(&orth);
		}
	}

	arrowLeft->Draw(&orth);
	arrowRight->Draw(&orth);
}

void StageSelectScene::Reset()
{
	mainCamera.Reset();

	uiDisplayer->SetUIMode(UIDisplayer::UIMode::StageSelect);

	initialized = false;
	selected = false;
}

void StageSelectScene::Debug()
{
#ifdef USE_IMGUI

#endif // USE_IMGUI

}

void StageSelectScene::ReplaceObjects()
{
	if (initialized) return;

	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		// プレイヤータワーのインスタンス化 & IDセット
		for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
		{
			playerTowers[stageIndex][i]->ReplaceOnMap(static_cast<int32_t>(stageIndex));
		}
		// エネミータワーのインスタンス化 & IDセット
		for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
		{
			enemyTowers[stageIndex][i]->ReplaceOnMap(static_cast<int32_t>(stageIndex));
		}
		// エネミーファクトリーのインスタンス化 & IDセット
		for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
		{
			enemyFactories[stageIndex][i]->ReplaceOnMap(static_cast<int32_t>(stageIndex));
		}
		// グラウンドのインスタンス化 & IDセット
		grounds[stageIndex][0]->ReplaceOnMap(static_cast<int32_t>(stageIndex));
	}


	initialized = true;
}
