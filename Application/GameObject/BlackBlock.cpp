#include "BlackBlock.h"

void BlackBlock::Update()
{
	model->Update();
}

void BlackBlock::Init()
{
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
}

