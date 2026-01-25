#include "PostEffectBuffer.h"
#include "../../../commonVariables.h"


void PostEffectBuffer::CreateRTV(ID3D12Device* device_, RtvDescriptorHeap* rtvDescHeap_,
	D3D12_RENDER_TARGET_VIEW_DESC desc_)
{
	colorBuffer.CreateRTV(device_, rtvDescHeap_, desc_, shaderBuffer.Getter_Resource());

	colorBuffer.SetDXMatrix(CommonV::kWindow_W, CommonV::kWindow_H);

}

ShaderBuffer* PostEffectBuffer::GetShaderBuffer()
{
	return &shaderBuffer;
}

D3D12_CPU_DESCRIPTOR_HANDLE* PostEffectBuffer::GetRtvHandle()
{
	return colorBuffer.Getter_Handle();
}

uint16_t* PostEffectBuffer::GetSrvHandle()
{
	return &srvHandle;
}