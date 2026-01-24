#pragma once
#include "./pipelineSet/pipelineSet.h"
#include <memory>

class VpShaders;

class AllPipelineSet
{
public:
	static int const kNumShaderSet = 20;

private:
	//[ pipelineSet ]
	std::unique_ptr<PipelineSet> pipelineSets[kNumShaderSet][kCountOfBlendMode][kCountOfCullMode];

	VpShaders* vpShaders = nullptr;
	ID3D12Device* device = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;

	void Add(std::string shaderSetName_, bool isTopologyLine = false);

public:

	void Initialize(ID3D12Device* device_, VpShaders* vpShaders_, ID3D12GraphicsCommandList* commandList_);
	void CreateNewPipeline(
		std::string folderPath_,
		std::string vsFileName_,
		std::string psFileName_,
		std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> inputElementDescCreateFunc_,
		std::function<std::vector<D3D12_ROOT_PARAMETER>()> rootParameterCreateFunc_,
		bool isTopologyLine_ = false);

	inline auto* Getter_pipelineSet(int shaderSetIndex_,BlendMode blendMode_,CullMode cullMode_)
	{
		return pipelineSets[shaderSetIndex_][blendMode_][cullMode_].get();
	}
};

