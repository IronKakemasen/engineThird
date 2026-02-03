#include "UIDisplayer.h"
#include "imgui.h"
#include ",,/../../Json/Json.h"
#include "GameObjectManager.h"
#include "../InGameController/InGameController.h"
#include "../../Config/InGameConfig.h"
#include <array>


UIDisplayer::UIDisplayer()
{
	buttonSelectCoolTime.Initialize(0.1f);
	easingCounter.Initialize(0.1f);

	std::map<uiType, Vector2> uiTexureSize;
	// 汎用
	uiTexureSize[uiType::Numbers1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Cursor50x50] = Vector2{ 50.0f,50.0f };
	// 操作説明UI
	uiTexureSize[uiType::Back200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Decision200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Move200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Option200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Pause200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Reticle200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Set200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Shot200x60] = Vector2{ 200.0f,60.0f };
	uiTexureSize[uiType::Zoom200x60] = Vector2{ 200.0f,60.0f };
	// ポーズUI
	uiTexureSize[uiType::PauseTitle500x100] = Vector2{ 500.0f,100.0f };
	uiTexureSize[uiType::PauseButton01_350x50] = Vector2{ 350.0f,50.0f };
	uiTexureSize[uiType::PauseButton02_350x50] = Vector2{ 350.0f,50.0f };
	uiTexureSize[uiType::PauseButton03_350x50] = Vector2{ 350.0f,50.0f };
	uiTexureSize[uiType::PauseButton04_350x50] = Vector2{ 350.0f,50.0f };
	uiTexureSize[uiType::PauseScreen_1280x720] = Vector2{ 1280.0f,720.0f };
	// インゲームUI
	uiTexureSize[uiType::GameOver1000x200] = Vector2{ 1000.0f,200.0f };
	uiTexureSize[uiType::StageClear1000x200] = Vector2{ 1000.0f,200.0f };
	// ステージセレクト
	uiTexureSize[uiType::Stage1Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage2Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage3Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage4Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage5Name1000x100] = Vector2{ 1000.0f,100.0f };

	std::map<uiType, TextureTag> uiTexure;
	// 汎用
	uiTexure[uiType::Numbers1000x100] = TextureTag::kNumbers1000x100;
	uiTexure[uiType::Cursor50x50] = TextureTag::kCursor50x50;
	// 操作説明UI
	uiTexure[uiType::Back200x60] = TextureTag::kButtonBack200x60;
	uiTexure[uiType::Decision200x60] = TextureTag::kButtonDecision200x60;
	uiTexure[uiType::Move200x60] = TextureTag::kButtonMove200x60;
	uiTexure[uiType::Option200x60] = TextureTag::kButtonOption200x60;
	uiTexure[uiType::Pause200x60] = TextureTag::kButtonPause200x60;
	uiTexure[uiType::Reticle200x60] = TextureTag::kButtonReticle200x60;
	uiTexure[uiType::Set200x60] = TextureTag::kButtonSet200x60;
	uiTexure[uiType::Shot200x60] = TextureTag::kButtonShot200x60;
	uiTexure[uiType::Zoom200x60] = TextureTag::kButtonZoom200x60;
	// ポーズUI
	uiTexure[uiType::PauseTitle500x100] = TextureTag::Pause500x100;
	uiTexure[uiType::PauseButton01_350x50] = TextureTag::PauseButton01_350x50;
	uiTexure[uiType::PauseButton02_350x50] = TextureTag::PauseButton02_350x50;
	uiTexure[uiType::PauseButton03_350x50] = TextureTag::PauseButton03_350x50;
	uiTexure[uiType::PauseButton04_350x50] = TextureTag::PauseButton04_350x50;
	uiTexure[uiType::PauseScreen_1280x720] = TextureTag::PauseScreen_1280x720;
	// インゲームUI
	uiTexure[uiType::GameOver1000x200] = TextureTag::kGameOver1000x200;
	uiTexure[uiType::StageClear1000x200] = TextureTag::StageClear1000x200;
	// ステージセレクト
	uiTexure[uiType::Stage1Name1000x100] = TextureTag::kStageName1000x100;
	uiTexure[uiType::Stage2Name1000x100] = TextureTag::kStageName1000x100;
	uiTexure[uiType::Stage3Name1000x100] = TextureTag::kStageName1000x100;
	uiTexure[uiType::Stage4Name1000x100] = TextureTag::kStageName1000x100;
	uiTexure[uiType::Stage5Name1000x100] = TextureTag::kStageName1000x100;

	for (size_t i = 0; i < uiTexureSize.size(); i++)
	{
		uiElements[uiType(i)].sprite = std::make_unique<Sprite>();
		uiElements[uiType(i)].sprite->Initialize(
			uiTexureSize[uiType(i)].x,
			uiTexureSize[uiType(i)].y,
			{ uiElements[uiType(i)].initPosition.x,
				uiElements[uiType(i)].initPosition.y,0.0f },
			M::GetInstance()->GetTexIndex(uiTexure[uiType(i)]),
			{ 255,255,255,255 });
	}
}

void UIDisplayer::Update()
{
	// ポーズUI更新
	UpdatePauseUI();

	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.pos =
		{ 
			uiElements[drawOrder[i]].initPosition.x + uiElements[drawOrder[i]].posOffset.x, 
			uiElements[drawOrder[i]].initPosition.y + uiElements[drawOrder[i]].posOffset.y,
			0.0f };

		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.scale =
		{
			uiElements[drawOrder[i]].initScale.x + uiElements[drawOrder[i]].scaleOffset.x,
			uiElements[drawOrder[i]].initScale.y + uiElements[drawOrder[i]].scaleOffset.y,
			1.0f };
	}
}

void UIDisplayer::Init()
{
	SetIdentity(Tag::kUIManager);
}

void UIDisplayer::Reset()
{
	std::vector<GameObject*> inGameControllerList = gameObjectManager->Find(GameObject::Tag::kInGameController);
	inGameController = reinterpret_cast<InGameController*>(inGameControllerList[0]);

	// いーじんぐ初期化
	preOffset = pauseScreenOffset;
	pauseCounter.Initialize(1.0f);
	currentSelectedButton = 0;
	buttonSelectCoolTime.Initialize(0.1f);
	easingCounter.Initialize(0.1f);
	selected = false;
}

void UIDisplayer::LoadData()
{
	for (size_t i = 0; i < size_t(uiType::MAX); i++)
	{
		uiType type = uiType(i);

		std::string mode = toString(this->mode);
		std::string tex = toString(type);
		std::string key = "/" + mode + "/" + tex;

		Json::LoadParam(path, key + "/pos", uiElements[type].initPosition);
		Json::LoadParam(path, key + "/scale", uiElements[type].initScale);
	}
}
void UIDisplayer::SaveData()
{
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiType type = drawOrder[i];

		std::string mode = toString(this->mode);
		std::string tex = toString(type);
		std::string key = "/" + mode + "/" + tex;

		Json::SaveParam(path, key + "/pos", uiElements[type].initPosition);
		Json::SaveParam(path, key + "/scale", uiElements[type].initScale);
	}
	Json::Save(path);
}

void UIDisplayer::UpdatePauseUI()
{
	// モード切り替え				(ポーズ⇔プレイ)
	HandlePauseToggleInput();
	// イージングとオフセット更新	(ポーズ画面のスライドイン・アウト)
	UpdatePauseEasing();

	// ポーズ中なら
	if (gameObjectManager->isStop)
	{
		// カーソル更新				(上下移動 & 決定処理)
		UpdatePauseCursor();
	}

	// 決定処理が完了していたらモード切り替え要求を確定させる
	FinalizePauseSelectionIfReady();
}

// モード切り替え入力処理
void UIDisplayer::HandlePauseToggleInput()
{
	// START でポーズトグル
	if (M::GetInstance()->getPadState.IsJustPressed(0, PAD_START))
	{
		gameObjectManager->TheWorld();
		preOffset = pauseScreenOffset;
		pauseCounter.Initialize(1.0f);

		// ポーズスクリーン登場側ならカーソル位置リセット
		if (!gameObjectManager->isStop)
		{
			currentSelectedButton = 0;
		}
	}

#ifdef _DEBUG
	if (M::GetInstance()->IsKeyTriggered(KeyType::ESCAPE))
	{
		gameObjectManager->TheWorld();
		preOffset = pauseScreenOffset;
		pauseCounter.Initialize(1.0f);
	}
#endif
}

// ポーズ画面イージング更新
void UIDisplayer::UpdatePauseEasing()
{
	float t = pauseCounter.count;
	if (t > 1.0f) t = 1.0f;

	if (gameObjectManager->isStop)
	{
		pauseScreenOffset = Easing::EaseOutCubic(preOffset, 1000.0f, t);
	}
	else
	{
		if (pauseScreenOffset > 0.0f)
		{
			pauseScreenOffset = Easing::EaseOutCubic(preOffset, 0.0f, t);
		}
	}

	ApplyPauseXOffset(-pauseScreenOffset);
	pauseCounter.Add();
}
void UIDisplayer::ApplyPauseXOffset(float xOffset)
{
// イージング一括適用関数
	uiElements[uiType::PauseScreen_1280x720].posOffset.x = xOffset;
	uiElements[uiType::PauseButton01_350x50].posOffset.x = xOffset;
	uiElements[uiType::PauseButton02_350x50].posOffset.x = xOffset;
	uiElements[uiType::PauseButton03_350x50].posOffset.x = xOffset;
	uiElements[uiType::PauseButton04_350x50].posOffset.x = xOffset;
	uiElements[uiType::PauseTitle500x100].posOffset.x = xOffset;
	uiElements[uiType::Cursor50x50].posOffset.x = xOffset;
}

// ポーズカーソル更新
void UIDisplayer::UpdatePauseCursor()
{
	if (selected) return;

	// 入力処理
	UpdatePauseCursorInput();
	// 決定処理
	HandlePauseDecisionInput();
	// イージング更新
	UpdatePauseCursorEasing();

	buttonSelectCoolTime.Add();
	easingCounter.Add();
}
void UIDisplayer::UpdatePauseCursorInput()
{
	bool up = false;
	bool down = false;
	if (M::GetInstance()->getPadState.IsHeld(0, PAD_UP) ||
		M::GetInstance()->getPadState.GetLeftStick(0).y > inGameConfig->deadZone)
		up = true;
	if (M::GetInstance()->getPadState.IsHeld(0, PAD_DOWN) ||
		M::GetInstance()->getPadState.GetLeftStick(0).y < -inGameConfig->deadZone)
		down = true;

	if (!up && !down)
	{
		buttonHeldFrameCount = 0;
	}
	else // 選択切り替え(イージング前座標保存・上下選択クールタイム設定・イージングカウンター初期化)
	{
		buttonHeldFrameCount++;
	}

	// クールタイム中は入力受付しない
	if (buttonSelectCoolTime.count < 1.0f)
	{
		// 連打された時にクールタイムを無視できるように0.01で初期化
		//if (M::GetInstance()->getPadState.IsJustReleased(0, PAD_UP) ||
		//	M::GetInstance()->getPadState.IsJustReleased(0, PAD_DOWN))
		if ((preDown && !down) || (preUp && !up))
		{
			buttonSelectCoolTime.Initialize(0.01f);
		}
		return;
	}

	preUp = up;
	preDown = down;


	if (up || down) // 選択切り替え(イージング前座標保存・上下選択クールタイム設定・イージングカウンター初期化)
	{
		preButtonOffset = currentSelectedButton * 80.0f;
		bool isFastRepeat = false;
		if (buttonHeldFrameCount > 30)
		{
			isFastRepeat = true;
		}
		buttonSelectCoolTime.Initialize(isFastRepeat ? 0.1f : 0.5f);
		easingCounter.Initialize(0.1f);

		if (up)
		{
			currentSelectedButton--;
			if (currentSelectedButton < 0) currentSelectedButton = 2;
		}
		else if (down)
		{
			currentSelectedButton++;
			if (currentSelectedButton > 2) currentSelectedButton = 0;
		}
	}
}
void UIDisplayer::HandlePauseDecisionInput()
{
	// 決定ボタンが押されていなければ抜ける
	if (!M::GetInstance()->getPadState.IsJustPressed(0, PAD_A)) return;

	// ここに来ているということはポーズ中で決定ボタンが押されたということ
	switch (currentSelectedButton)
	{
	case 0:	// プレイ
	case 1:	// リトライ
		// そして世界は再び動き出す
		gameObjectManager->TheWorld();
		// イージング初期化
		preOffset = pauseScreenOffset;
		// スライドアウト開始
		pauseCounter.Initialize(1.0f);
		// 決定フラグ立て
		selected = true;
		break;

	case 2:	// セレクト
		// そして世界は再び動き出す
		gameObjectManager->TheWorld();
		// 決定フラグ立て
		selected = true;
		break;

	default:
		break;
	}
}
void UIDisplayer::UpdatePauseCursorEasing()
{
	uiElements[uiType::Cursor50x50].posOffset.y = Easing::EaseOutCubic(
		preButtonOffset,
		currentSelectedButton * 80.0f,
		easingCounter.count);
}

// 決定処理完了確認＆確定
void UIDisplayer::FinalizePauseSelectionIfReady()
{
	// 決定処理が完了していなければ抜ける
	if (!selected) return;
	// イージングが完了していなければ抜ける
	if (!(pauseCounter.count >= 1.0f)) return;

	switch (currentSelectedButton)
	{
	case 0:	// プレイ
		pauseRequest = PauseRequest::kNone;
		break;
	case 1:	// リトライ
		pauseRequest = PauseRequest::kRetry;
		break;
	case 2:	// セレクト
		pauseRequest = PauseRequest::kBackToStageSelect;
		break;
	default:
		break;
	}

	selected = false;
}



void UIDisplayer::SetUIMode(UIMode mode_)
{
	pauseScreenOffset = 0.0f;

	mode = mode_;

	drawOrder.clear();

	switch (mode)
	{
	case UIDisplayer::UIMode::TiTle:
		break;
	case UIDisplayer::UIMode::StageSelect:
		drawOrder.push_back(uiType::Decision200x60);	// ケッテイ　アイコン
		drawOrder.push_back(uiType::Option200x60);		// セッテイ　アイコン
		drawOrder.push_back(uiType::Back200x60);		// モドル　　アイコン
		break;
	case UIDisplayer::UIMode::InGame:
		drawOrder.push_back(uiType::Move200x60);		// イドウ　　アイコン
		drawOrder.push_back(uiType::Shot200x60);		// ショット　アイコン
		drawOrder.push_back(uiType::Reticle200x60);		// ネラウ　　アイコン
		drawOrder.push_back(uiType::Pause200x60);		// ポーズ　　アイコン
		drawOrder.push_back(uiType::Zoom200x60);		// ズーム　　アイコン

		drawOrder.push_back(uiType::PauseScreen_1280x720);	// ポーズ背景
		drawOrder.push_back(uiType::PauseButton01_350x50);	// プレイ
		drawOrder.push_back(uiType::PauseButton02_350x50);	// リトライ
		drawOrder.push_back(uiType::PauseButton04_350x50);	// セレクト
		drawOrder.push_back(uiType::PauseTitle500x100); 	// ポーズタイトル

		drawOrder.push_back(uiType::Cursor50x50);	// カーソル
		break;
	case UIDisplayer::UIMode::None:
		break;
	default:
		break;
	}

	// このモードのUIの初期位置と初期スケールをロード
	LoadData();

	// 初期位置と初期スケールにリセット
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].posOffset = Vector2(0.0f, 0.0f);
		uiElements[drawOrder[i]].scaleOffset = Vector2(0.0f, 0.0f);
	}
}

void UIDisplayer::SuperDraw(Matrix4 * ortho_)
{
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].sprite->Draw(ortho_);
	}
}

UIDisplayer::PauseRequest UIDisplayer::GetPauseRequest()
{
	PauseRequest out = pauseRequest;
	pauseRequest = PauseRequest::kNone;
	return out;

}


void UIDisplayer::DebugDraw()
{
#ifdef USE_IMGUI
	ImGui::Begin("UI Debug");

	if (ImGui::Button("Save UI Data")) SaveData();

	std::array<bool, size_t(uiType::MAX)> isDraw = {};
	isDraw.fill(false);

	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		isDraw[size_t(drawOrder[i])] = true;

		ImGui::Text("%s", toString(drawOrder[i]).c_str());
		ImGui::DragFloat2(("pos" + std::to_string(i)).c_str(),
			&uiElements[drawOrder[i]].initPosition.x, 1.0f);
		ImGui::DragFloat2(("scale" + std::to_string(i)).c_str(),
			&uiElements[drawOrder[i]].initScale.x, 0.1f);
	}

	ImGui::End();
#endif // USE_IMGUI
}

void UIDisplayer::Draw(Matrix4* vpMat_)
{/**/}

void UIDisplayer::SetCollisionBackTable()
{/**/}
