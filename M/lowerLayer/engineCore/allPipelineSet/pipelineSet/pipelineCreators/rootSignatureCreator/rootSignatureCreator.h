#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "../pipelineComponents.h"
#include <utility>
#include <string>

class RootSignatureCreator
{
	D3D12_DESCRIPTOR_RANGE descriptorRange[1];

	D3D12_ROOT_PARAMETER GetRootParaMeterPixelShader(int registerNum_);
	D3D12_ROOT_PARAMETER GetRootParaMeterVertexShader(int registerNum_);
	D3D12_ROOT_PARAMETER GetRootParaMeterDescriptorRange();
	//いつか修正
	std::pair<D3D12_ROOT_PARAMETER*, UINT> GetRootParameters(std::string shaderSetName_);

public:
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12RootSignature >CreateRootSignature(
		ID3D12Device* device_,
		std::string shaderSetName_);

};
