#pragma once
#include "../../../../../utilities/vectorAndMatrix/vectorAndMatrix.h"

struct Material
{
	Vector3 diffuse;
	float pad1;
	Vector3 specular;
	float pad2;
	Vector4 albedoColor;
	Matrix4 uvTransform;
	float roughness = 0.0f;
	float metalic = 0.0f;
	float shininess = 0.0f;

};



