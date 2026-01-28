#include "UIDisplayer.h"
#include "imgui.h"

void UIDisplayer::Update()
{}

void UIDisplayer::Init()
{}

void UIDisplayer::Reset()
{}

void UIDisplayer::LoadData()
{}
void UIDisplayer::SaveData()
{}

void UIDisplayer::SetUIMode(UIMode mode_)
{
	mode = mode_;

	drawOrder.clear();

	switch (mode)
	{
	case UIDisplayer::UIMode::TiTle:
		drawOrder.push_back(size_t(uiType::Move900x250));
		drawOrder.push_back(size_t(uiType::Option900x250));
		drawOrder.push_back(size_t(uiType::Back900x250));
		break;
	case UIDisplayer::UIMode::StageSelect:
		break;
	case UIDisplayer::UIMode::InGame:
		break;
	case UIDisplayer::UIMode::None:
		break;
	default:
		break;
	}

}

void UIDisplayer::SuperDraw(Matrix4 * vpMat_)
{
	switch (mode)
	{
	case UIDisplayer::UIMode::TiTle:
		DrawTitleUI(vpMat_);
		break;
	case UIDisplayer::UIMode::StageSelect:
		DrawStageSelectUI(vpMat_);
		break;
	case UIDisplayer::UIMode::InGame:
		DrawInGameUI(vpMat_);
		break;
	case UIDisplayer::UIMode::None:
		break;
	default:
		break;
	}
}

void UIDisplayer::DrawTitleUI(Matrix4 * vpMat_)
{}

void UIDisplayer::DrawStageSelectUI(Matrix4 * vpMat_)
{
	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[uiType(drawOrder[i])].sprite->Draw(vpMat_);
	}
}

void UIDisplayer::DrawInGameUI(Matrix4 * vpMat_)
{

}

void UIDisplayer::DebugDraw()
{
	ImGui::Begin("UI Debug");

	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[uiType(i)].sprite->GetAppearance()->trans.pos;
	}

	ImGui::End();
}

UIDisplayer::UIDisplayer()
{
	LoadData();

	std::map<uiType, Vector2> uiTexureSize;
	uiTexureSize[uiType::Back900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Decision900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Move900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Option900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Pause900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Shot900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Zoom900x250] = Vector2{ 900.0f,250.0f };
	uiTexureSize[uiType::Numbers100x100] = Vector2{ 100.0f,100.0f };
	uiTexureSize[uiType::Stage1Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage2Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage3Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage4Name1000x100] = Vector2{ 1000.0f,100.0f };
	uiTexureSize[uiType::Stage5Name1000x100] = Vector2{ 1000.0f,100.0f };

	for (size_t i = 0; i < drawOrder.size(); i++)
	{
		uiElements[uiType(i)].sprite = std::make_unique<Sprite>();
		uiElements[uiType(i)].sprite->Initialize(
			uiTexureSize[uiType(i)].x,
			uiTexureSize[uiType(i)].y,
			{	uiElements[uiType(i)].position.x,
				uiElements[uiType(i)].position .y,0.0f },
			M::GetInstance()->GetTexIndex(TextureTag::kButtonBack900x250));
	}
}

void UIDisplayer::Draw(Matrix4* vpMat_)
{/**/}

void UIDisplayer::SetCollisionBackTable()
{/**/}
