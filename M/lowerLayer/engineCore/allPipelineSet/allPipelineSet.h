#pragma once
#include "./pipelineSet/pipelineSet.h"
#include <memory>

class VPShaderTable;

class AllPipelineSet
{
	static int const numShaderSet = 5;
	//[ pipelineSet ]
	std::unique_ptr<PipelineSet> pipelineSets[numShaderSet][kCountOfBlendMode][kCountOfCullMode];

	VPShaderTable* vpShaderTable = nullptr;
	ID3D12Device* device = nullptr;

	void CreateAllGraphicsPipelineSets(ID3D12Device* device_, VPShaderTable* vpShaderTable_);
	


public:

	inline void Setter_ShaderSetNameList(VPShaderTable* vpShaderTable_)
	{
		vpShaderTable = vpShaderTable_;
	}

	inline void Setter_Device(ID3D12Device* device_)
	{
		device = device_;
	}

	void Initialize(ID3D12Device* device_, VPShaderTable* vpShaderTable_);
	void Add(std::string shaderSetName_, bool isTopologyLine = false);

};

