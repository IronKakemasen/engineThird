#include "SampleObj.h"

void SampleObj::Update()
{

}

void SampleObj::Init()
{
	trans.pos = { 0.0f,0.0f,2.0f };
}

void SampleObj::Reset()
{

}

void SampleObj::Draw(Matrix4* vpMat_)
{
	sModel.Draw(vpMat_);
}


SampleObj::SampleObj()
{
	for (Appearance& appearance : sModel.model->Getter_ModelData().appearance)
	{
		appearance.trans.parent = &trans;
	}	
}