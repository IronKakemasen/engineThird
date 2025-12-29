#pragma once
#include "../../math/vector/vector.h"

struct LightBasePara
{
	Vector3 pos;
	float intensity;
	Vector3 color;
	int isActive;
};

struct PointLightPara
{
	Vector3 pos;
	float intensity;
	Vector3 color;
	float invSqrRadius;
	int isActive;
};


struct LightBehavior 
{
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
};

