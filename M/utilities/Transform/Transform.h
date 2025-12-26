#pragma once
#include "../vectorAndMatrix/vectorAndMatrix.h"
#include "../Quaternion/Quaternion.h"
#include "../benriTemplateFunc/benriTempFunc.h"

struct Transform
{
	Vector3 pos;
	Vector3 scale;
	Vector3 rotation;
	Quaternion quaternion;

	Transform* parent = nullptr;

	Matrix4 GetWorldMatrix();
	void BeChildren(Transform* parent_);
	Vector3 GetWorldPos();

	Transform();
};

