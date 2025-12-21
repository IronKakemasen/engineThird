#pragma once
#include "../../../../../utilities/vectorAndMatrix/vectorAndMatrix.h"


struct Material
{
	Vector4 albedoColor;
	Matrix4 uvTransform;
	float roughness = 0.0f;  
	//float pad_roughness[3];
	float metallic = 0.0f;;
	//float pad_metallic[3];

	//Vector4 albedoColor;
	//Matrix4 uvTransform;

};


