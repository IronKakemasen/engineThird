#include "UIDisplayer.h"

void UIDisplayer::Update()
{}

void UIDisplayer::Init()
{}

void UIDisplayer::Reset()
{}

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

}

void UIDisplayer::DrawInGameUI(Matrix4 * vpMat_)
{}

UIDisplayer::UIDisplayer()
{
	buttonBack900x250 = std::make_unique<Sprite>();
	buttonDecision900x250 = std::make_unique<Sprite>();
	buttonMove900x250 = std::make_unique<Sprite>();
	buttonOption900x250 = std::make_unique<Sprite>();
	buttonPause900x250 = std::make_unique<Sprite>();
	buttonShot900x250 = std::make_unique<Sprite>();
	buttonZoom900x250 = std::make_unique<Sprite>();
	numbers100x100 = std::make_unique<Sprite>();

	stage1Name1000x100 = std::make_unique<Sprite>();
	stage2Name1000x100 = std::make_unique<Sprite>();
	stage3Name1000x100 = std::make_unique<Sprite>();
	stage4Name1000x100 = std::make_unique<Sprite>();
	stage5Name1000x100 = std::make_unique<Sprite>();
}

void UIDisplayer::Draw(Matrix4* vpMat_)
{/**/}

void UIDisplayer::SetCollisionBackTable()
{/**/}
