#include "UIDisplayer.h"
#include "imgui.h"
#include ",,/../../Json/Json.h"
#include <array>

void UIDisplayer::Update()
{
}

void UIDisplayer::Init()
{
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.pos =
		{ uiElements[drawOrder[i]].position.x, uiElements[drawOrder[i]].position.y,0.0f };
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.scale =
		{ uiElements[drawOrder[i]].scale.x,uiElements[drawOrder[i]].scale.y,1.0f };
	}
	SetIdentity(Tag::kUIManager);
}

void UIDisplayer::Reset()
{}

void UIDisplayer::LoadData()
{
	for (size_t i = 0; i < size_t(uiType::MAX); i++)
	{
		uiType type = uiType(i);

		std::string mode = toString(this->mode);
		std::string tex = toString(type);
		std::string key = "/" + mode + "/" + tex;

		Json::LoadParam(path, key + "/pos", uiElements[type].position);
		Json::LoadParam(path, key + "/scale", uiElements[type].scale);
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

		Json::SaveParam(path, key + "/pos", uiElements[type].position);
		Json::SaveParam(path, key + "/scale", uiElements[type].scale);
	}
	Json::Save(path);
}

void UIDisplayer::SetUIMode(UIMode mode_)
{
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
		drawOrder.push_back(uiType::Cursor50x50);	// カーソル
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
		drawOrder.push_back(uiType::PauseButton03_350x50);	// オプション
		drawOrder.push_back(uiType::PauseButton04_350x50);	// セレクト
		drawOrder.push_back(uiType::PauseTitle500x100); 	// ポーズタイトル

		drawOrder.push_back(uiType::Cursor50x50);	// カーソル
		break;
	case UIDisplayer::UIMode::None:
		break;
	default:
		break;
	}

	LoadData();
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.pos =
		{ uiElements[drawOrder[i]].position.x, uiElements[drawOrder[i]].position.y,0.0f };
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.scale =
		{ uiElements[drawOrder[i]].scale.x,uiElements[drawOrder[i]].scale.y,1.0f };
	}
}

void UIDisplayer::SuperDraw(Matrix4 * ortho_)
{
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[drawOrder[i]].sprite->Draw(ortho_);
	}
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
		ImGui::SameLine();
		ImGui::DragFloat2(("pos" + std::to_string(i)).c_str(),
			&uiElements[drawOrder[i]].position.x, 1.0f);
		ImGui::DragFloat2(("scale" + std::to_string(i)).c_str(),
			&uiElements[drawOrder[i]].scale.x, 0.1f);

		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.pos =
		{ uiElements[drawOrder[i]].position.x, uiElements[drawOrder[i]].position.y,0.0f };
		uiElements[drawOrder[i]].sprite->GetAppearance()->trans.scale =
		{ uiElements[drawOrder[i]].scale.x,uiElements[drawOrder[i]].scale.y,1.0f };
	}

	for (size_t i = 0; i < uiElements.size(); i++)
	{
		if (isDraw[i]) continue;

		if (ImGui::Button(("Add : " + toString(uiType(i))).c_str()))
		{
			drawOrder.push_back(uiType(i));
			LoadData();
		}
	}

	ImGui::End();
#endif // USE_IMGUI
}

UIDisplayer::UIDisplayer()
{
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
			{ uiElements[uiType(i)].position.x,
				uiElements[uiType(i)].position.y,0.0f },
			M::GetInstance()->GetTexIndex(uiTexure[uiType(i)]),
			{ 255,255,255,255 });

		// 初期位置とスケールをセット
		uiElements[uiType(i)].sprite->GetAppearance()->trans.pos =
		{ uiElements[uiType(i)].position.x, uiElements[uiType(i)].position.y,0.0f };
		uiElements[uiType(i)].sprite->GetAppearance()->trans.scale =
		{ uiElements[uiType(i)].scale.x,uiElements[uiType(i)].scale.y,1.0f };
	}
}

void UIDisplayer::Draw(Matrix4* vpMat_)
{/**/}

void UIDisplayer::SetCollisionBackTable()
{/**/}
