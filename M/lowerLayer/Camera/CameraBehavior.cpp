#include "CameraBehavior.h"


CameraPara::CameraPara()
{
	fov = CommonV::FOVy;
	trans.interpolationCoe = 0.05f;
}

void CameraBehavior::DirectionInterpolate()
{

}

void CameraBehavior::SetViewProjectionMat()
{
	Matrix4 worldMat = para.trans.GetWorldMatrix();
	Matrix4 viewMat = worldMat.GetInversed();
	float aspectRatio = CommonV::kWindow_W / CommonV::kWindow_H;
	Matrix4 projMat = Get_PerspectiveFOV(para.fov, aspectRatio);

	vpMat = viewMat.Multiply(projMat);
}