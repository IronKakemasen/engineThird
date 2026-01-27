#include "groundM.h"

void groundM::Update()
{

}

void groundM::Init()
{
	// モデルの初期化
	model->Init(&trans);

}

void groundM::Reset()
{

}
void groundM::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}
void groundM::SetCollisionBackTable()
{

}

groundM::groundM()
{
	model.reset(new GroundPlane);
}
