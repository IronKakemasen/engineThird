#include "ParticleMeshSrvCreator.h"
#include "../../../Data/ShaderBufferData/ShaderBufferData.h"
#include "../../../../meshStructure/TransformMatrix/TransformMatrix.h"
#pragma comment(lib,"d3d12.lib")


D3D12_SHADER_RESOURCE_VIEW_DESC ParticleMeshSrvCreator::CreateSRVDesc(UINT maxParticle_)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC ret_desc{};

	ret_desc.Format = DXGI_FORMAT_UNKNOWN;
	ret_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	ret_desc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

	ret_desc.Buffer.FirstElement = 0;
	ret_desc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	ret_desc.Buffer.NumElements = maxParticle_;
	ret_desc.Buffer.StructureByteStride = sizeof(TransformMatrix);

	return ret_desc;
}

uint16_t ParticleMeshSrvCreator::CreateSRVForParticle(ShaderBuffer* shaderBuffer_,UINT maxParticle_)
{
	ShaderBuffer shaderBuffer;
	shaderBuffer.resource = CreateBufferResource(device, sizeof(TransformMatrix) * maxParticle_);

	D3D12_SHADER_RESOURCE_VIEW_DESC desc = CreateSRVDesc(maxParticle_);
	uint16_t ret_index = CreateSRV(desc, &shaderBuffer);

	shaderBufferData->data.emplace_back(shaderBuffer);

#ifdef USE_IMGUI
	return ret_index - 1;
#endif // USE_IMGUI

	return ret_index;
}

