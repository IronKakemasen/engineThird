#pragma once
#include "../vectorAndMatrix/vectorAndMatrix.h"



struct Quaternion
{
	Vector3 axis = { 0.0f,0.0f,1.0f };
	float deltaTheta = 0.0f;

	Vector4 Get();
	Matrix4 GetRotateMat();
	Vector4 LookAt();

private:
	Vector4 ConvertToQuaternion(Matrix4 m);


};

