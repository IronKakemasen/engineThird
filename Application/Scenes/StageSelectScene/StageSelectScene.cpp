#include "StageSelectScene.h"
#include "../../utilities/Json/Json.h"

void StageSelectScene::Update()
{
	//if (M::GetInstance()->IsKeyTriggered(KeyType::Q))
	//{
	//	SceneBehavior::doReset = true;
	//}

	//mainCamera.Update();

	//// みたいにカメラターゲットを変える？
	//mainCamera.player = player[0][0].get();
	//// カメラは固定？


	//AdaptToPostEffect();
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

void StageSelectScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	//for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	//{
	//	// プレイヤー描画
	//	for (size_t i = 0; i < player[stageIndex].size(); ++i)
	//	{
	//		player[stageIndex][i]->Draw(vpMat);
	//	}
	//	// テスト地面描画
	//	for (size_t i = 0; i < shikouteis[stageIndex].size(); ++i)
	//	{
	//		shikouteis[stageIndex][i]->Draw(vpMat);
	//	}
	//	// プレイヤータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
	//	{
	//		playerTowers[stageIndex][i]->Draw(vpMat);
	//	}
	//	// プレイヤーアリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < allies[stageIndex].size(); ++i)
	//	{
	//		allies[stageIndex][i]->Draw(vpMat);
	//	}
	//	// プレイヤーバレットのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerBullets[stageIndex].size(); ++i)
	//	{
	//		playerBullets[stageIndex][i]->Draw(vpMat);
	//	}
	//	// エネミーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemies[stageIndex].size(); ++i)
	//	{
	//		enemies[stageIndex][i]->Draw(vpMat);
	//	}
	//	// エネミータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
	//	{
	//		enemyTowers[stageIndex][i]->Draw(vpMat);
	//	}
	//	// エネミーファクトリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
	//	{
	//		enemyFactories[stageIndex][i]->Draw(vpMat);
	//	}
	//}

}

void StageSelectScene::Reset()
{
	mainCamera.Reset();
}

void StageSelectScene::Debug()
{
#ifdef USE_IMGUI



	//ImGui::Begin("InGameController");
	//ImGui::Text(("Mode  : " + inGameController->WathchInString()).c_str());
	//ImGui::Text("Count : %.1f", *inGameController->GetCnt());
	//ImGui::End();


	//for (int i = 0; i < 2; ++i)
	//{
	//	auto* r = rectLights[i]->Getter_Para();
	//	ImGui::Begin(("RectLight" + std::to_string(i)).c_str());
	//	ImGui::DragFloat("intensity", &r->intensity);
	//	ImGui::DragFloat3("pos", reinterpret_cast<float*>(&r->pos));
	//	ImGui::DragFloat3("lookDir", reinterpret_cast<float*>(rectLights[i]->GetLookDirection()), 0.02f);
	//	ImGui::DragFloat3("color", reinterpret_cast<float*>(&r->color));
	//	ImGui::DragFloat("rad", &r->attenuationRadius);

	//	ImGui::End();

	//}



#endif // USE_IMGUI

}


