#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <functional>
#include "../../allShaderData/vpShaderTable/vpShaderTable.h"
#include "./pipelineCreators/pipelineCreators.h"
#include <assert.h>
#pragma comment(lib,"d3d12.lib")


class PipelineSet
{
	static inline PipelineCreators pipelineCreators;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineStateObject = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	std::vector<D3D12_ROOT_PARAMETER> rootParameters;
	ID3D12GraphicsCommandList* commandList = nullptr;


public:

	void SetGraphicsRootSignature();
	void SetPipelineState();

	template<typename... Args>
	void SetConstantBufferViews(Args... args_)
	{
		uint8_t length = sizeof...(args_);
		D3D12_GPU_VIRTUAL_ADDRESS virtualGpuAdress[] = { args_... };

		size_t limit = rootParameters.size();

		if (length > limit - 1 )
		{
			assert(false);
		}

		for (int i = 0; i < length; i++)
		{
			commandList->SetGraphicsRootConstantBufferView(i + 1, virtualGpuAdress[i]);
		}
	}




	static [[nodiscard]] std::unique_ptr<PipelineSet> CreateGraphicsPipelineSet(ID3D12Device* device_, 
		std::string shaderSetName_,
		VPShaderTable* vpShaderTable_,
		BlendMode blendMode_,
		CullMode cullMode_,
		bool isTopologyLine = false);

	void Activate_RootparameterCreateFunc(std::function<std::vector<D3D12_ROOT_PARAMETER>()> func_);
	void Activate_InputLayoutCreateFunc(std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> func_);

	inline void Setter_Commandlist(ID3D12GraphicsCommandList* commandList_)
	{
		commandList = commandList_;
	}


	inline auto* Getter_CommandList()
	{
		return commandList;
	}


};
