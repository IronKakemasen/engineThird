#include "UIObject.h"

void UIObject::Update()
{

}

void UIObject::Init()
{
	model->Init(&trans);
}
void UIObject::Reset()
{

}
void UIObject::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}
void UIObject::SetCollisionBackTable()
{

}

UIObject::UIObject()
{
	model.reset(new UIPlane);
}
