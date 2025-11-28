#include "MQuad.h"

void MQuad::Update()
{

}

void MQuad::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawMQuad(leftTop, rightTop, rightBottom,leftBottom,
		color, texHandle, drawMode, blendMode, cullMode,shaderSetIndex,
		trans, uvTrans, *vpMat_);
}
