#include "Player.h"

void Player::Update()
{
	model->Update();
}

void Player::Init()
{
	SetIdentity(kPlayer);
	model->Init();
	trans.pos = { 102,109,101 };
}

void Player::Reset()
{
	model->Reset();

}

void Player::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

Player::Player()
{
	model.reset(new PlayerModel);
	model->MakeAllPartsBeChildren(&trans);
}

