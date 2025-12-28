#pragma once
#include "../../math/vector/vector.h"

struct LightBasePara
{
	Vector3 pos;
	float pad1;
	Vector3 color;
	float intensity;
};

struct PointLightPara:LightBasePara
{
	float radius;
};


struct LightBehavior 
{
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
};

