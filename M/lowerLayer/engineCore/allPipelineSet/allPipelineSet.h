#pragma once
#include "./pipelineSet/pipelineSet.h"
#include <memory>


class VpShaders;


class AllPipelineSet
{
public:
	static int const kNumShaderSet = 5;

private:
	//[ pipelineSet ]
	std::unique_ptr<PipelineSet> pipelineSets[kNumShaderSet][kCountOfBlendMode][kCountOfCullMode];

	VpShaders* vpShaders = nullptr;
	ID3D12Device* device = nullptr;
	ID3D12CommandList* commandList = nullptr;




public:

	void Initialize(ID3D12Device* device_, VpShaders* vpShaders_, ID3D12CommandList* commandList_);
	void CreateNewPipeline(
		std::string vsFileName_,
		std::string psFileName_,
		std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> inputElementDescCreateFunc_,
		std::function<std::vector<D3D12_ROOT_PARAMETER>()> rootParameterCreateFunc_);


	void Add(std::string shaderSetName_, bool isTopologyLine = false);

};

