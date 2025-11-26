#include "CameraBehavior.h"

void CameraBehavior::SetViewProjectionMat()
{
	Matrix4 worldMat = trans.GetWorldMatrix();
	Matrix4 viewMat = worldMat.GetInversed();
	float aspectRatio = CommonV::kWindow_W / CommonV::kWindow_H;
	Matrix4 projMat = Get_PerspectiveFOV(CommonV::FOVy, aspectRatio);

	vpMat = viewMat.Multiply(projMat);
}