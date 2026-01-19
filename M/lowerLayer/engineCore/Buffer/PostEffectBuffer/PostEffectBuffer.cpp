#include "PostEffectBuffer.h"

ShaderBuffer* PostEffectBuffer::GetShaderBuffer()
{
	return &shaderBuffer;
}

D3D12_CPU_DESCRIPTOR_HANDLE* PostEffectBuffer::GetRtvHandle()
{
	return &renderTargetHandle;
}

uint16_t* PostEffectBuffer::GetSrvHandle()
{
	return &srvHandle;
}