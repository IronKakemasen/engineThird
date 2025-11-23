#include "CameraBehavior.h"

void CameraBehavior::SetViewProjectionMat()
{
	Matrix4 worldMat = trans.GetWorldMatrix();
	Matrix4 viewMat = worldMat.GetInversed();
	float aspectRatio = V_Common::kWindow_W / V_Common::kWindow_H;
	Matrix4 projMat = Get_PerspectiveFOV(V_Common::FOVy, aspectRatio);

	vpMat = viewMat.Multiply(projMat);
}