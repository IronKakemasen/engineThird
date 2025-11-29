#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "../pipelineComponents.h"
#include <utility>
#include <string>
#include <functional>
#include <vector>

class RootSignatureCreator
{
	int sum_created = 0;

	inline static D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};

	std::vector<std::function<std::vector<D3D12_ROOT_PARAMETER>()>> funcs_rootParametersCreate;
	std::pair<D3D12_ROOT_PARAMETER*, UINT> heap_rootParametersAndSum;

	void CopyFromIndex(int funcIndex_);
	void SetRootParameters(int index_);

public:

	void RecordRootparameters(std::vector<D3D12_ROOT_PARAMETER>& dst_ , int funcIndex_);

	static D3D12_ROOT_PARAMETER GetRootParameterWithDescriptorRange(
		D3D12_DESCRIPTOR_RANGE* descriptorRange_,
		D3D12_SHADER_VISIBILITY visibility_,
		UINT numDescriptors_);

	static D3D12_ROOT_PARAMETER GetRootParaMeterPixelShader(int registerNum_);
	static D3D12_ROOT_PARAMETER GetRootParaMeterVertexShader(int registerNum_);
	static void SetDescriptorRange(D3D12_DESCRIPTOR_RANGE* dst_,
		D3D12_DESCRIPTOR_RANGE_TYPE rangeType_, int registerNum_);

	void AddToFuncs_RootParametersCreate(std::function<std::vector<D3D12_ROOT_PARAMETER>()> func_);

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12RootSignature >CreateRootSignature(
		ID3D12Device* device_,
		int index_, std::string shaderSetName_);

};
