#include "SampleModel.h"

void SampleModel::Update()
{

}

void SampleModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

SampleModel::SampleModel()
{
	model = M::GetInstance()->CreateModel("./M/resource/preset/model/teapot.obj");
}
