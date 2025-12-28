#pragma once
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../Buffer/constantBuffer/PointLightBuffer/PointLightBuffer.h"

#include <memory>

class ExclusiveDraw;


class LightCreator
{
	ExclusiveDraw* exclusiveDraw = nullptr;
	ID3D12Device* device = nullptr;

	std::pair<std::unique_ptr < DirectionalLightBuffer >,
		std::unique_ptr < DirectionalLight > > dirLightSet;

	std::pair<std::unique_ptr < PointLightBuffer >,
		std::unique_ptr < PointLight > > pLightSet;

	int const pLightCreationLimit = 10;

public:
	DirectionalLight* CreateDirectionalLight();
	PointLight* CreatePointLight();
	void Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_);
};

