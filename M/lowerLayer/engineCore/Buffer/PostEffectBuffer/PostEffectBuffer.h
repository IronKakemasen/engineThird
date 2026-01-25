#pragma once
#include "../gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../gpuResources/Resource/colorBuffer/colorBuffer.h"
#include "../gpuResourcesBehavior.h"
#include <assert.h>
#include <memory>

class PostEffectBuffer
{
	ShaderBuffer shaderBuffer;
	ColorBuffer colorBuffer;
	uint16_t srvHandle;

public:
	PostEffectBuffer() {};
	ShaderBuffer* GetShaderBuffer();
	D3D12_CPU_DESCRIPTOR_HANDLE* GetRtvHandle();
	uint16_t* GetSrvHandle();
	void CreateRTV(ID3D12Device* device_, RtvDescriptorHeap* rtvDescHeap_,
		D3D12_RENDER_TARGET_VIEW_DESC desc_);
	inline ColorBuffer* GetColorBuffer() { return &colorBuffer; }
};

