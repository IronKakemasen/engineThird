#include "Shikoutei.h"

void Shikoutei::Update()
{
	shikoModel->Update();
}

void Shikoutei::Init()
{
	shikoModel->Init();
}

void Shikoutei::Reset()
{
	shikoModel->Reset();
}

void Shikoutei::Draw(Matrix4* vpMat_)
{
	shikoModel->Draw(vpMat_);
}

void Shikoutei::SetCollisionBackTable()
{

}

Shikoutei::Shikoutei()
{
	shikoModel.reset(new ShikouteiModel);
}
