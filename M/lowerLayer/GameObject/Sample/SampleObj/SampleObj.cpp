#include "SampleObj.h"

void SampleObj::Update()
{

}

void SampleObj::Init()
{
	trans.pos = { 0.0f,2.2f,0.4f};
	sModel->Init();
	sModel2->Init();

}

void SampleObj::Reset()
{

}

void SampleObj::Draw(Matrix4* vpMat_)
{
	sModel->Draw(vpMat_);
	sModel2->Draw(vpMat_);
}


SampleObj::SampleObj()
{
	sModel.reset(new SampleModel);
	sModel2.reset(new SampleModel2);

	for (Appearance& appearance : *sModel->model->Getter_Appearance())
	{
		appearance.trans.BeChildren(&trans);
	}	

	for (Appearance& appearance : *sModel2->model->Getter_Appearance())
	{
		appearance.trans.BeChildren(&trans);
	}

}

void SampleObj::SetCollisionBackTable()
{

}
