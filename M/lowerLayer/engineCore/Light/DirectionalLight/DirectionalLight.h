#pragma once
#include "../LightBehavior.h"

struct DirectionalLightBuffer;

class DirectionalLight:LightBehavior
{
	DirectionalLightBuffer* dirLightBuffer = nullptr;

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


	DirectionalLight(DirectionalLightBuffer* dirLightBuffer_);

};

