#include "SamplePlayer.h"

void SamplePlayer::Update()
{

}

void SamplePlayer::Init()
{
	trans.pos = {-3.0f,0.0f,0.0f};
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
	quadModel.Initialize(30.0f, 30.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2),
		{ 255,255,255,255});
	quadModel.appearance.trans.rotation.x = 90.0f;
	quadModel.appearance.roughness = 0.0f;
	quadModel.appearance.metalic = 0.0f;

}