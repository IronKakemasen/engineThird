#include "Quaternion.h"
#include "../ConvertToRadian/ConvertToRadian.h"
#include <math.h>

Matrix4 Quaternion::GetRotateMat()
{
	Vector4  c_ = Get();

	float a00 = (c_.x * c_.x) - (c_.y * c_.y) - (c_.z * c_.z) + (c_.w * c_.w);
	float a01 = (c_.x * c_.y - c_.z * c_.w) * 2.0f;
	float a02 = (c_.x * c_.z + c_.y * c_.w) * 2.0f;

	float a10 = (c_.x * c_.y + c_.z * c_.w) * 2.0f;
	float a11 = -(c_.x * c_.x) + (c_.y * c_.y) - (c_.z * c_.z) + (c_.w * c_.w);
	float a12 = (c_.y * c_.z - c_.x * c_.w) * 2.0f;

	float a20 = (c_.x * c_.z - c_.y * c_.w) * 2.0f;
	float a21 = (c_.y * c_.z + c_.x * c_.w) * 2.0f;
	float a22 = -(c_.x * c_.x) - (c_.y * c_.y) + (c_.z * c_.z) + (c_.w * c_.w);
	return Matrix4
	{
		a00, a10, a20, 0.0f,
		a01, a11, a21, 0.0f,
		a02, a12, a22, 0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
}

Vector4 Quaternion::Get()
{
	float radian = GetRadian(deltaTheta);
	Vector3 buff = Vector3{ axis }.GetNormalized();
	float halfRad = radian * V_Common::kHalf;
	float sinNum = sinf(halfRad);

	Vector4 quaternion = { buff.x * sinNum,buff.y * sinNum
		,buff.z * sinNum ,cosf(halfRad) };

	return quaternion;
}

Vector4 Quaternion::LookAt()
{
	Vector3 z = axis.GetNormalized();
	Vector3 ver = { 0.0f, 1.0f, 0.0f };
	Vector3 x = (ver.GetCross(z)).GetNormalized();
	Vector3 y = (z.GetCross(x)).GetNormalized();

	Matrix4 m =
	{
		x.x,y.x,z.x,0.0f,
		x.y,y.y,z.y,0.0f,
		x.z,y.z,z.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return ConvertToQuaternion(m);
}

Vector4 Quaternion::ConvertToQuaternion(Matrix4 m)
{
	float elem[4];
	elem[0] = m.m[0][0] - m.m[1][1] - m.m[2][2] + 1.0f;
	elem[1] = -m.m[0][0] + m.m[1][1] - m.m[2][2] + 1.0f;
	elem[2] = -m.m[0][0] - m.m[1][1] + m.m[2][2] + 1.0f;
	elem[3] = m.m[0][0] + m.m[1][1] + m.m[2][2] + 1.0f;

	int biggestIdx = 0;

	for (int i = 0; i < 4; i++)
	{
		if (elem[i] > elem[biggestIdx])
		{
			biggestIdx = i;
		}
	}

	if (elem[biggestIdx] < 0)
	{
		return Vector4();
	}

	float q[4];
	float v = sqrtf(elem[biggestIdx]) * 0.5f;
	q[biggestIdx] = v;
	float mult = 0.25f / v;

	switch (biggestIdx)
	{
	case 0:
		q[1] = (m.m[1][0] + m.m[0][1]) * mult;
		q[2] = (m.m[0][2] + m.m[2][0]) * mult;
		q[3] = (m.m[2][1] - m.m[1][2]) * mult;
		break;
	case 1:
		q[0] = (m.m[1][0] + m.m[0][1]) * mult;
		q[2] = (m.m[2][1] + m.m[1][2]) * mult;
		q[3] = (m.m[0][2] - m.m[2][0]) * mult;
		break;
	case 2:
		q[0] = (m.m[0][2] + m.m[2][0]) * mult;
		q[1] = (m.m[2][1] + m.m[1][2]) * mult;
		q[3] = (m.m[1][0] - m.m[0][1]) * mult;
		break;
	case 3:
		q[0] = (m.m[2][1] - m.m[1][2]) * mult;
		q[1] = (m.m[0][2] - m.m[2][0]) * mult;
		q[2] = (m.m[1][0] - m.m[0][1]) * mult;
		break;
	}

	return Vector4 {q[0], q[1], q[2], q[3]};
}
