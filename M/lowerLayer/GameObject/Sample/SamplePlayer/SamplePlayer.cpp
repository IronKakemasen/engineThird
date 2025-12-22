#include "SamplePlayer.h"

void SamplePlayer::Update()
{

}

void SamplePlayer::Init()
{
	trans.translate = {-3.0f,0.0f,0.0f};
}

void SamplePlayer::Reset()
{

}

void SamplePlayer::Draw(Matrix4* vpMat_)
{
	quadModel.Draw(vpMat_);
}


SamplePlayer::SamplePlayer()
{
	quadModel.appearance.trans.parent = &trans;
	quadModel.Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kPlayer));
}