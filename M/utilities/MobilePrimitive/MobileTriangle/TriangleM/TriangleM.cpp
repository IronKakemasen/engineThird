#include "TriangleM.h"

void TriangleM::Update()
{

}

void TriangleM::Draw(Matrix4& vpMat_)
{
	M::GetInstance()->DrawMTriangle(left,top,right,color,texHandle,drawMode,blendMode,cullMode,
	trans,uvTrans, vpMat_);
}
