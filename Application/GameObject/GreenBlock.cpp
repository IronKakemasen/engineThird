#include "GreenBlock.h"

void GreenBlock::Update()
{
	model->Update();

}

void GreenBlock::Init()
{
	SetIdentity(kGreen);
	model->Init();
}

void GreenBlock::Reset()
{
	model->Reset();

}

void GreenBlock::Draw(Matrix4* vpMat_)
{

	model->Draw(vpMat_);

}

GreenBlock::GreenBlock()
{
	model.reset(new GreenModel);
	(*model->model->Getter_Appearance())[0].color = { 62,179,112,255 };
	model->MakeAllPartsBeChildren(&trans);

}

