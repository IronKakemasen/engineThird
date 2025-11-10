#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include "../../allShaderData/vpShaderTable/vpShaderTable.h"
#include "./pipelineCreators/pipelineCreators.h"

class PipelineSet
{
	static inline PipelineCreators pipelineCreators;

	//Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineStateObject = nullptr;
	//Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;


public:

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineStateObject = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;

	static [[nodiscard]] std::unique_ptr<PipelineSet> CreateGraphicsPipelineSet(ID3D12Device* device_, 
		std::string shaderSetName_,
		VPShaderTable* vpShaderTable_,
		BlendMode blendMode_,
		CullMode cullMode_,
		bool isTopologyLine = false);

	//inline void Setter_RootSignature(ID3D12RootSignature* dst_)
	//{
	//	rootSignature = dst_;
	//}

	//inline void Setter_PipelineStateObject(ID3D12PipelineState* dst_)
	//{
	//	pipelineStateObject = dst_;
	//}

	//inline auto* Getter_PipelineStateObject()
	//{
	//	return pipelineStateObject.Get();
	//}



	//inline auto* Getter_RootSignature()
	//{
	//	return rootSignature.Get();
	//}

	//inline auto* Getter_PipelineStateObject()
	//{
	//	return pipelineStateObject.Get();
	//}

};
