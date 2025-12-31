#include "NormalBlock.h"

void NormalBlock::Update()
{
	model->Update();
}

void NormalBlock::Init()
{
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
}

