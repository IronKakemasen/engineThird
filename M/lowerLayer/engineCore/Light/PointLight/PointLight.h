#pragma once
#include "../LightBehavior.h"

struct PointLightBuffer;

class PointLight :LightBehavior, PointLightPara

{
	PointLightBuffer* pLightBuffer = nullptr;

public:
	virtual void Update() override;
	virtual void Init() override;
	virtual void Reset() override;
	inline auto* Getter_Pos()
	{
		return &pos;
	}
	inline auto* Getter_Intensity()
	{
		return &intensity;
	}
	inline auto* Getter_Color()
	{
		return &color;
	}


	PointLight(PointLightBuffer* pLightBuffer_);

};

