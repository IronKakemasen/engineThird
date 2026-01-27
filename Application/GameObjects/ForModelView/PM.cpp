#include "PM.h"
void PM::Update()
{

}

void PM::Init()
{
	// モデルの初期化
	model->Init(&trans);

}

void PM::Reset()
{

}
void PM::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}
void PM::SetCollisionBackTable()
{

}

PM::PM()
{
	model.reset(new PlayerModel);
}
