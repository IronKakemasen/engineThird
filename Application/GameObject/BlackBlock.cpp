#include "BlackBlock.h"

void BlackBlock::Update()
{
	model->Update();
}

void BlackBlock::Init()
{
	SetIdentity(kBlack);
	model->Init();
}

void BlackBlock::Reset()
{
	model->Reset();

}

void BlackBlock::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

BlackBlock::BlackBlock()
{
	model.reset(new BlackModel);
	(*model->model->Getter_Appearance())[0].color = { 32,32,32,255 };
}

