#include "GroundPlane.h"

GroundPlane::GroundPlane()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModel01/PlayerModel01.obj");
}

void GroundPlane::Update()
{

}

void GroundPlane::Draw(Matrix4* vpMat_)
{

}

void GroundPlane::Init(Transform* gameObjectTrans_)
{

}

void GroundPlane::Reset()
{

}
