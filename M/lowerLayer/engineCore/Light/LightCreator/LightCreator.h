#pragma once
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../Buffer/constantBuffer/PointLightBuffer/PointLightBuffer.h"
#include "../../Buffer/StructuredBuffer/PointLightStructuredBuffer/PointLightStructuredBuffer.h"

#include <memory>

class ExclusiveDraw;
class StructuredBufferSrvCreator;

class LightCreator
{
	std::pair<std::unique_ptr < DirectionalLightBuffer >,
		std::unique_ptr < DirectionalLight > > dirLightSet;
	std::unique_ptr < PointLightStructuredBuffer > pLightStructuredBuffer;
	std::vector<std::unique_ptr<PointLight>> pointLightContainer;
	//srvのインデックス
	uint16_t srvIndex;

	int const kSumPLight = 25;
	void CreatePointLight(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_,
		StructuredBufferSrvCreator* srvCreator_);
	void CreateDirectionalLight(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_);

public:
	LightCreator();
	void Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_, 
		StructuredBufferSrvCreator* srvCreator_);
	inline auto* Getter_DirLight()
	{
		return dirLightSet.second.get();
	}
	inline auto* Getter_DirLightBuffer()
	{
		return dirLightSet.first.get();
	}

	inline auto* Getter_PointLightContainer()
	{
		return &pointLightContainer;
	}

	inline auto* Getter_PointLightStructuredBuffer()
	{
		return pLightStructuredBuffer.get();
	}

};

