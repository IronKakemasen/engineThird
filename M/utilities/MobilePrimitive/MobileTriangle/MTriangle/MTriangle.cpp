#include "MTriangle.h"

void MTriangle::Update()
{

}

void MTriangle::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawMTriangle(left, top, right, color, texHandle, drawMode, blendMode, cullMode,shaderSetIndex,
		trans, uvTrans, *vpMat_);
}
