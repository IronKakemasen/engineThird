#include "TenkyuuClass.h"

void TenkyuuClass::Update()
{

}

void TenkyuuClass::Init()
{
	model->Init(&trans);
}
void TenkyuuClass::Reset()
{

}
void TenkyuuClass::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}
void TenkyuuClass::SetCollisionBackTable()
{

}

TenkyuuClass::TenkyuuClass()
{
	model.reset(new Tenkyu);
}
