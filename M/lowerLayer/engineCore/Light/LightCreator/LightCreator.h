#pragma once
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include <memory>

class ExclusiveDraw;


class LightCreator
{
	
	ExclusiveDraw* exclusiveDraw = nullptr;
	ID3D12Device* device = nullptr;

	std::pair<std::unique_ptr < DirectionalLightBuffer >,
		std::unique_ptr < DirectionalLight > > dirLightSet;

public:
	DirectionalLight* CreateDirecctoinalLight();
	void Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_);
};

