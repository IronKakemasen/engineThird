#include "Transform.h"

Matrix4 Transform::GetWorldMatrix()
{
	//ターゲット方向のクォータニオン
	quaternion.axis = quaternion.axis.GetNormalized();
	Benri::Adjust(quaternion.axis.z, -0.00001f, 0.00001f, 0.00001f);
	Vector4 tmp = quaternion.LookAt();

	Matrix4 ret_world = Get_SQrTMat3D(scale, tmp, translate);

	if (parent)
	{
		Matrix4 parentMat = parent->GetWorldMatrix();
		ret_world = ret_world.Multiply(parentMat);
	}

	return ret_world;
}

void Transform::BeChildren(Transform* parent_)
{
	parent = parent_;
}

Vector3 Transform::GetWorldPos()
{
	Matrix4 wMat = GetWorldMatrix();

	return
	{
		wMat.m[3][0],
		wMat.m[3][1],
		wMat.m[3][2],
	};
}

Transform::Transform()
{
	scale = { 1.0f,1.0f,1.0f };
}