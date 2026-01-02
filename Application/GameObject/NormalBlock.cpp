#include "NormalBlock.h"

void NormalBlock::Update()
{
	model->Update();
}

void NormalBlock::Init()
{
	SetIdentity(kNormal);
	model->Init();

}

void NormalBlock::Reset()
{
	model->Reset();

}

void NormalBlock::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

NormalBlock::NormalBlock()
{
	model.reset(new NormalModel);
	model->MakeAllPartsBeChildren(&trans);

}

