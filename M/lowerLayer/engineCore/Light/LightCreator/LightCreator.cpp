#include "LightCreator.h"
#include "../../Render/ExclusiveDraw/ExclusiveDraw.h"
#include "../../Buffer/gpuResources/Creator/SrvCreator/StructuredBufferSrvCreator/StructuredBufferSrvCreator.h"

LightCreator::LightCreator()
{

}

void LightCreator::CreatePointLight(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_, 
	StructuredBufferSrvCreator* srvCreator_)
{
	pLightStructuredBuffer.reset(new PointLightStructuredBuffer);
	pLightStructuredBuffer->pLight.CreateAndMapping(device_, kSumPLight);

	for (int i = 0; i < kSumPLight; ++i)
	{
		pointLightContainer.emplace_back(std::make_unique<PointLight>());
	}

	//SRVの作成
	srvIndex = srvCreator_->CreateSRVForParticle(kSumPLight, sizeof(PointLightPara),
		pLightStructuredBuffer->pLight.shaderBuffer);

	exclusiveDraw_->Setter_PLightSrvIndex(&srvIndex);

}

void LightCreator::CreateDirectionalLight(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_)
{

	dirLightSet.first.reset(new DirectionalLightBuffer);
	dirLightSet.second.reset(new DirectionalLight());

	dirLightSet.first->dirLight.CreateAndMapping(device_);
	exclusiveDraw_->Setter_DirectionalLightBuffer(dirLightSet.first.get());
}

void LightCreator::Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_,
	StructuredBufferSrvCreator* srvCreator_)
{
	CreatePointLight(exclusiveDraw_,device_,srvCreator_);
	CreateDirectionalLight(exclusiveDraw_, device_);
}
