#pragma once
#include "../LightCreator/LightCreator.h"

class LightManager
{
	std::vector<PointLight*> pointLights;
	PointLightStructuredBuffer* pointLightStructuredBuffer = nullptr;
	DirectionalLightBuffer* dirLightBuffer = nullptr;

	DirectionalLight* directionalLight = nullptr;
	LightCreator lightCreator;
	int pointLightID;

	void Fetch();
	void Batch();
public:

	DirectionalLight* ExportDirectionalLight();
	PointLight* ExportPointLight();

	LightManager();

	void Update();
	void Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_,
		StructuredBufferSrvCreator* srvCreator_);
	
	inline auto* Getter_LightCreator()
	{
		return &lightCreator;
	}
};

