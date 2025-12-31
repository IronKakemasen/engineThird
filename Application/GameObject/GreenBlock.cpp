#include "GreenBlock.h"

void GreenBlock::Update()
{
	model->Update();

}

void GreenBlock::Init()
{
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

}

