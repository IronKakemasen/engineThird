#include "Player.h"

void Player::Update()
{
	model->Update();
}

void Player::Init()
{
	model->Init();
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
}

