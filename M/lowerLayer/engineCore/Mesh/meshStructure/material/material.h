#pragma once
#include "../../../../../utilities/vectorAndMatrix/vectorAndMatrix.h"

//
//struct Material
//{
//	Vector4 albedoColor;
//	Matrix4 uvTransform;
//	float roughness = 0.0f;  
//	//float pad_roughness[3];
//	float metallic = 0.0f;;
//	//float pad_metallic[3];
//
//	//Vector4 albedoColor;
//	//Matrix4 uvTransform;
//
//};


struct Material
{
	Vector3 diffuse;
	float pad1;
	Vector3 specular;
	float pad2;
	Vector4 albedoColor;
	Matrix4 uvTransform;
	float roughness = 0.0f;
	float metallic = 0.0f;
	float shininess = 0.0f;

	//float pad_roughness[3];
	//float pad_metallic[3];
	//Vector4 albedoColor;
	//Matrix4 uvTransform;


};



