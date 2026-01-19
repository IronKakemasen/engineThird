#pragma once
#include "../gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../gpuResourcesBehavior.h"
#include <assert.h>
#include <memory>

class PostEffectBuffer
{
	ShaderBuffer shaderBuffer;
	D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle;
	uint16_t srvHandle;
public:
	ShaderBuffer* GetShaderBuffer();
	D3D12_CPU_DESCRIPTOR_HANDLE* GetRtvHandle();
	uint16_t* GetSrvHandle();
};

